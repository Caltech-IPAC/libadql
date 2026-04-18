#include "../Top_Level_Parser.hxx"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

using phoenix::at_c;
using phoenix::push_back;
using qi::char_;
using qi::lit;
using qi::raw;
using qi::labels::_1;
using qi::labels::_a;
using qi::labels::_val;

//=======================================================

ADQL::Top_Level_Parser::Top_Level_Parser()
        : Top_Level_Parser::base_type(query, "top_level_parser") {
    single_quoted = '\'' >> *(char_ - '\'') >> '\'';
    single_quoted.name("single_quoted");

    double_quoted = '"' >> *(char_ - '"') >> '"';
    double_quoted.name("double_quoted");

    parenthesized = '(' >> *(opaque_token) >> ')';
    parenthesized.name("parenthesized");

    // Opaque tokens, to be consumed without inspecting contents:
    opaque_token = single_quoted | double_quoted | parenthesized | (char_ - '(' - ')');
	// Quoted strings cannot nest, but parenthetical strings
	// can. Close-parentheses in particular must be non-opaque so that
	// we can keep track of how deeply we are nested.

	// As long as `parenthesized` precedes `(char_ - '(' - ')')` in
	// the definition of `opaque`, open-parentheses will always be
	// treated as the opening of a `parenthesized` and will never fall
	// through to `(char_ - '(' - ')')`.
    opaque_token.name("opaque_token");

    // UNION [ALL|DISTINCT]
    union_op = raw[ascii::no_case[lit("UNION")] >> &ascii::space >>
                   -(+ascii::space >>
                     (ascii::no_case[lit("DISTINCT")] | ascii::no_case[lit("ALL")]) >>
                     &(ascii::space | qi::eoi))];
    union_op.name("union_op");

    // Trailing clauses: everything from the first trailing keyword to end of input.
    trailing_clauses = raw[((ascii::no_case[lit("HAVING")] >> &ascii::space) |
                            (ascii::no_case[lit("GROUP")] >> +ascii::space >>
                             ascii::no_case[lit("BY")] >> &ascii::space) |
                            (ascii::no_case[lit("ORDER")] >> +ascii::space >>
                             ascii::no_case[lit("BY")] >> &ascii::space)) >>
                           *(opaque_token)];
    trailing_clauses.name("trailing_clauses");

    // A single SELECT...FROM...WHERE component: everything up to
    // UNION, a trailing clause keyword, or end of input.
    select_from_where_component =
            raw[ascii::no_case[lit("SELECT")] >> &ascii::space >>
                *(opaque_token - (ascii::no_case[lit("UNION")] >> &ascii::space) -
                  (ascii::no_case[lit("HAVING")] >> &ascii::space) -
                  (ascii::no_case[lit("GROUP")] >> &ascii::space) -
                  (ascii::no_case[lit("ORDER")] >> &ascii::space))];
    select_from_where_component.name("select_from_where_component");

    // WITH clause: everything from WITH up to the first depth-0 SELECT.
    with_clause =
            raw[ascii::no_case[lit("WITH")] >> &ascii::space >>
                *(opaque_token - (ascii::no_case[lit("SELECT")] >> &ascii::space))];
    with_clause.name("with_clause");

    // Top-level query
    query = (-with_clause[at_c<0>(_val) = _1]) >> *ascii::space >>
            (select_from_where_component[push_back(
                     at_c<1>(_val),
                     phoenix::construct<std::pair<std::string, std::string>>(
                             std::string(), _1))] >>
             *(*ascii::space >> union_op[_a = _1] >> +ascii::space >>
               select_from_where_component[push_back(
                       at_c<1>(_val),
                       phoenix::construct<std::pair<std::string, std::string>>(
                               _a, _1))])) >>
            *ascii::space >> (-trailing_clauses[at_c<2>(_val) = _1]);
    query.name("query");

#ifdef DEBUG_SPLITTER
    BOOST_SPIRIT_DEBUG_NODE(single_quoted);
    BOOST_SPIRIT_DEBUG_NODE(double_quoted);
    BOOST_SPIRIT_DEBUG_NODE(parenthesized);
    BOOST_SPIRIT_DEBUG_NODE(opaque_token);
    BOOST_SPIRIT_DEBUG_NODE(union_op);
    BOOST_SPIRIT_DEBUG_NODE(trailing_clauses);
    BOOST_SPIRIT_DEBUG_NODE(select_from_where_component);
    BOOST_SPIRIT_DEBUG_NODE(with_clause);
    BOOST_SPIRIT_DEBUG_NODE(query);
#endif
}

//=======================================================

ADQL::Top_Level_Components ADQL::parse_top_level(const std::string &input) {
    Top_Level_Components top_level_components;
    auto begin = input.cbegin();
    auto end = input.cend();
    Top_Level_Parser top_level_splitter;
    bool ok = parse(begin, end, top_level_splitter, top_level_components);
    if (!ok || begin != end) {
        throw std::runtime_error("Top_Level_Parser failed at: " +
                                 std::string(begin, end));
    }
    return top_level_components;
}
