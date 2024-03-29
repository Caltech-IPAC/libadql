#include "../../ADQL_parser.hxx"

void ADQL_parser::init_search_condition() {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::alnum;
    using boost::spirit::qi::alpha;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::hold;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::labels::_val;
    using boost::spirit::qi::lexeme;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::lower;
    using boost::spirit::qi::no_skip;
    using boost::spirit::qi::omit;
    using boost::spirit::qi::print;
    using boost::spirit::qi::ulong_long;
    namespace ascii = boost::spirit::ascii;

    boolean_primary %= predicate | hold[lit('(') >> search_condition >> lit(')')] |
                       value_expression_non_bool;

    boolean_factor %= -lexeme[ascii::no_case[ascii::string("NOT")] >>
                              &boost::spirit::qi::space] >>
                      boolean_primary;

    boolean_term %= boolean_factor >> lexeme[(ascii::no_case[ascii::string("AND")] |
                                              ascii::no_case[ascii::string("OR")]) >>
                                             &boost::spirit::qi::space] >>
                    search_condition;

    /// FIXME: Make this a list parser instead of recursive
    boolean_value_expression %= boolean_term | boolean_factor;
    search_condition %= boolean_value_expression;

#ifdef DEBUG_WHERE
    BOOST_SPIRIT_DEBUG_NODE(boolean_primary);
    BOOST_SPIRIT_DEBUG_NODE(boolean_factor);
    BOOST_SPIRIT_DEBUG_NODE(boolean_term);
    BOOST_SPIRIT_DEBUG_NODE(boolean_value_expression);
    BOOST_SPIRIT_DEBUG_NODE(search_condition);
#endif
}
