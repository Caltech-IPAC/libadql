#include "../../ADQL_parser.hxx"

void ADQL_parser::init_columns() {
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

    column_name %= identifier;
    column_name.name("column_name");

    // JTODO some overlap with init_correlation_specification
    as = value_expression[at_c<0>(_val) = _1] >>
         lexeme[ascii::no_case["AS"] >> &boost::spirit::qi::space] >
         column_name[at_c<1>(_val) = _1];
    as.name("as");

    qualifier_star %= qualifier >> ascii::string(".*");
    non_as %= qualifier_star | value_expression;
    non_as.name("non_as");
    select_item %= as | non_as;
    select_list %= select_item % ',';
    columns %= ascii::string("*") | select_list;
    columns.name("columns");

#ifdef DEBUG_COL
    BOOST_SPIRIT_DEBUG_NODE(column_name);
    BOOST_SPIRIT_DEBUG_NODE(as);
    BOOST_SPIRIT_DEBUG_NODE(non_as);
    BOOST_SPIRIT_DEBUG_NODE(columns);
#endif
}
