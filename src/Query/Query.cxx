#include "../Query.hxx"

#include <iostream>

#include "ADQL_parser.hxx"
#include "Query_Preprocessor.hxx"
#include "Query_Preprocessor/Top_Level_Components.hxx"

// The Query class's constructor takes as input a query_string and,
// aided by the ADQL_parser, either populates the query_specification
// and other class members with data about the parsed query or fails
// with a message explaining why the query_string is not parseable.

// In order to get around an unpopular requirement imposed by the
// ADQL_parser, we intercept and preprocess the incoming query before
// handing off to the parser.  This interception is the work of
// Query_Preprocessor::preprocess(), which

// o Calls Top_Level_Parser to parse the query into top-level components
//   as described in Top_Level_Components.hxx

// o Iterates through the <union_op, search_from_where> pairs
//   constituting the Union_Op_And_SFW_Pairs element of
//   Top_Level_Components, calling Where_Clause_Normalizer to rewrite
//   the WHERE clauses in the form required by the ADQL_parser

// Query::Query then calls ADQL_parser on the 3 components of the
// (possibly modified) Top_Level_Components struct separately to
// complete the construction or throw an error as appropriate.

namespace {

//=======================================================
// Call parser through various entry points.
//=======================================================

void parse_sfw(const ADQL_parser &parser, ADQL::Select_From_Where &sfw,
               const std::string &input) {
    std::string::const_iterator begin(input.begin()), end(input.end());
    bool valid = phrase_parse(begin, end, parser.select_from_where,
                              boost::spirit::ascii::space, sfw);
    if (!valid || begin != end) {
        throw std::runtime_error("Error parsing SELECT...FROM...WHERE component: " +
                                 std::string(begin, end));
    }
}

//=======================================================

void parse_with(const ADQL_parser &parser, ADQL::With &with, const std::string &input) {
    std::string::const_iterator begin(input.begin()), end(input.end());
    bool valid =
            phrase_parse(begin, end, parser.with, boost::spirit::ascii::space, with);
    if (!valid || begin != end) {
        throw std::runtime_error("Error parsing WITH clause: " +
                                 std::string(begin, end));
    }
}

//=======================================================

void parse_trailing(const ADQL_parser &parser, ADQL::Query_Specification &query_spec,
                    const std::string &input) {
    std::string::const_iterator begin(input.begin()), end(input.end());
    // Try GROUP BY
    phrase_parse(begin, end, parser.group_by, boost::spirit::ascii::space,
                 query_spec.group_by);
    // Try HAVING
    phrase_parse(begin, end, parser.having, boost::spirit::ascii::space,
                 query_spec.having);
    // Try ORDER BY
    phrase_parse(begin, end, parser.order_by, boost::spirit::ascii::space,
                 query_spec.order_by);
    if (begin != end) {
        throw std::runtime_error("Error parsing trailing clauses: " +
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
    auto top_level_components = ADQL::Query_Preprocessor::preprocess(input);
    if (!top_level_components.with_clause_.empty()) {
        parse_with(parser, query_specification.with, top_level_components.with_clause_);
    }
    for (const auto &[op, sfw_str] : top_level_components.union_op_and_sfw_pairs_) {
        ADQL::Select_From_Where sfw_elt;
        parse_sfw(parser, sfw_elt, sfw_str);
        if (op.empty()) {
            query_specification.select_from_where_list.set_initial(sfw_elt);
        } else {
            query_specification.select_from_where_list.add_addon(op, sfw_elt);
        }
    }
    if (!top_level_components.trailing_clauses_.empty()) {
        parse_trailing(parser, query_specification,
                       top_level_components.trailing_clauses_);
    }
}
