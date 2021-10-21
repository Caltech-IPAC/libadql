#include "../../ADQL_parser.hxx"

void ADQL_parser::init_join() {
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

    join_specification %= join_condition | named_columns_join;
    join_specification.name("join specification");

    join_condition %= lexeme[ascii::no_case["ON"] >> &boost::spirit::qi::space] >>
                      search_condition;
    join_condition.name("join condition");

    named_columns_join %=
            lexeme[ascii::no_case["USING"] >> &boost::spirit::qi::space] >> '(' >
            join_column_list > ')';
    named_columns_join.name("named columns join");

    join_column_list %= column_name_list;
    join_column_list.name("join column list");

    column_name_list %= column_name % ',';
    column_name_list.name("column name list");

    table_correlation %= table_name >> -correlation_specification;

    outer_join = lexeme[(ascii::no_case[ascii::string("LEFT")] |
                         ascii::no_case[ascii::string("RIGHT")] |
                         ascii::no_case[ascii::string("FULL")]) >>
                        &boost::spirit::qi::space][at_c<0>(_val) = _1] >>
                 -lexeme[ascii::no_case[ascii::string("OUTER")] >>
                         &boost::spirit::qi::space][at_c<1>(_val) = true];
    outer_join.name("outer join type");

    join_type %= lexeme[ascii::no_case[ascii::string("INNER")] >>
                        &boost::spirit::qi::space] |
                 outer_join;
    join_type.name("join type");

    join_suffix = -(lexeme[ascii::no_case["NATURAL"] >> &boost::spirit::qi::space]
                          [at_c<0>(_val) = true]) >>
                  -join_type[at_c<1>(_val) = _1] >>
                  lexeme[ascii::no_case["JOIN"] >> &boost::spirit::qi::space] >
                  (table_reference[at_c<2>(_val) = _1] >>
                   -join_specification[at_c<3>(_val) = _1]);

    qualified_join %= ((lit('(') >> joined_table >> lit(')')) | table_correlation) >>
                      +join_suffix;
    qualified_join.name("qualified join");

    joined_table %= (qualified_join | (lit('(') >> joined_table >> lit(')')));
    joined_table.name("joined table");
}
