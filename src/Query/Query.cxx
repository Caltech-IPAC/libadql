#include "../Query.hxx"

#include <regex>

#include "ADQL_parser.hxx"

namespace {

//=======================================================
// Helper functions for preprocessing input query string
//=======================================================

//=======================================================

// Regex to determine whether WHERE clause of query_string
// consists of <left-search-condition AND geometric-constraint>
// optionally followed by < AND right-search-condition>.

static std::regex search_condition_on_left_of_geometry_regex(
        R"(WHERE ([^ ].+[^ ]) *AND *((?:(?:0|1) *= *)?(?:CONTAINS|INTERSECTS)(?:.*?(?= *(?:AND|HAVING|GROUP|ORDER|$))))(?: *AND *([^ ].+?(?= *(?:HAVING| GROUP| ORDER|$))))?(.*)$)",
        std::regex::icase);

//=======================================================

// Determine whether a single outermost pair of parentheses encloses
// both left_search_condition and geometric_constraint, e.g. "WHERE
// (x>1 AND CONTAINS(...)=1)".  If such a set of outermost enclosing
// parentheses is found, adjust the arguments to this function, which
// are passed by non-const reference, to drop those parentheses
// (leaving, in the same example, "WHERE x>1 AND CONTAINS(...)=1").
// In addition, check for a premature right parenthesis and determine
// whether geometric_constraint is contained in any pair of
// parentheses other than an outermost pair as above, and throw errors
// accordingly.

void check_and_adjust_parens(std::string &left_sc_str, std::string &geom_str) {
    assert(!left_sc_str.empty());
    assert(!geom_str.empty());

    ushort depth = 0;

    // Examine left_search_condition
    bool within_outermost = (left_sc_str[0] == '(');
    for (const char &c : left_sc_str) {
        if (c == '(') {
            ++depth;
        } else if (c == ')') {
            if (depth == 0) {
                throw std::runtime_error(
                        "Error: premature right parenthesis in WHERE clause I.");
            }
            --depth;
            if (depth == 0) {
                within_outermost = false;
            }
        }
    }

    if (depth > 1 || (depth == 1 && !within_outermost)) {
        throw std::runtime_error(
                "Error: inappropriate parentheses in WHERE "
                "clause I.");
    }

    // Examine geometric_constraint
    bool outermost_is_closed_at_end_of_geom = false;
    for (const char &c : geom_str) {
        if (outermost_is_closed_at_end_of_geom) {
            throw std::runtime_error(
                    "Error: inappropriate parentheses in WHERE clause II.");
        }

        if (c == '(') {
            ++depth;
        } else if (c == ')') {
            if (depth == 0) {
                throw std::runtime_error(
                        "Error: premature right parenthesis in WHERE clause II.");
            }
            --depth;
            if (depth == 0 && within_outermost) {
                // Assume we're at the end of geom_str; we'll throw an error in the next
                // iteration if it turns out that we're not.
                outermost_is_closed_at_end_of_geom = true;
            }
        }
    }

    if (outermost_is_closed_at_end_of_geom) {
        // Strip outermost paren from beginning of left_sc_str and end of
        // geom_str and let parser handle the rest.
        left_sc_str = left_sc_str.substr(1);
        geom_str = geom_str.substr(0, geom_str.size() - 1);
    }
}

//=======================================================

//=============================================================
// Rewrite query_string by moving a search condition from the left of
// a geometric constraint to its right, combining it using " AND "
// with the search condition on its right, if such exists.  This
// change simplifies the work of the parser.  For example,

// (x>1) AND CONTAINS(...)=1 AND y<2

// is rewritten as

//  CONTAINS(...)=1 AND (x>1) AND y<2

// =============================================================

std::string tweak_input_string(const std::string &input, const std::smatch &match) {
    assert(!left_sc_str.empty());
    assert(!geom_str.empty());

    std::stringstream replace_str_ss;

    std::string left_sc_str = match.str(1);
    std::string geom_str = match.str(2);
    std::string right_sc_str = match.str(3);

    check_and_adjust_parens(left_sc_str, geom_str);

    replace_str_ss << "WHERE " << geom_str << " AND ";
    replace_str_ss << left_sc_str;

    if (!right_sc_str.empty()) {
        replace_str_ss << " AND " << right_sc_str;
    }

    return std::regex_replace(input, search_condition_on_left_of_geometry_regex,
                              replace_str_ss.str());
}

//=======================================================
// Do the hard work.
//=======================================================

void parse_it(const ADQL_parser &parser, ADQL::Query_Specification &query_specification,
              const std::string &input) {
    std::string::const_iterator begin(input.begin()), end(input.end());
    bool valid(phrase_parse(begin, end, parser, boost::spirit::ascii::space,
                            query_specification));
    if (!valid) {
        auto error = parser.error_stream.str();
        if (error.empty()) error = "Error: Expecting <SELECT> here: \"" + input + "\"";
        ;
        throw std::runtime_error(error);
    } else if (begin != end) {
        throw std::runtime_error("Error: Unexpected terms at the end: " +
                                 std::string(begin, end));
    }
}

}  // namespace

//=======================================================
//=======================================================

ADQL::Query::Query(
        const std::string &input,
        const std::map<std::string, std::string> &table_mapping_for_columns) {
    ADQL_parser parser(table_mapping_for_columns);

    std::smatch match;
    bool is_match =
            std::regex_search(input, match, search_condition_on_left_of_geometry_regex);

    if (is_match) {
        parse_it(parser, query_specification, tweak_input_string(input, match));
    } else {
        parse_it(parser, query_specification, input);
    }
}
