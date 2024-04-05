#include "../../ADQL_parser.hxx"

void ADQL_parser::init_query() {
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

    with %= lexeme[ascii::no_case["WITH"] > &boost::spirit::qi::space] >
            with_table_name > -(lit('(') >> with_column_name % ',' > lit(')')) >>
            -(lexeme[ascii::no_case["AS"] > &boost::spirit::qi::space]) > subquery;

    with.name("with");

    with_table_name %= identifier;
    with_table_name.name("with_table_name");

    with_column_name %= identifier;
    with_column_name.name("with_column_name");

    where = lexeme[ascii::no_case["WHERE"] > &boost::spirit::qi::space] >

            ((geometry[at_c<0>(_val) = _1] >>
              -(ascii::no_case["AND"] > search_condition[at_c<1>(_val) = _1])) |

             ('(' >> geometry[at_c<0>(_val) = _1] > ')') |

             (search_condition[at_c<1>(_val) = _1]));

    where.name("where");

    where_no_geometry = lexeme[ascii::no_case["WHERE"] >> &boost::spirit::qi::space] >>
                        search_condition[at_c<1>(_val) = _1];
    where_no_geometry.name("where_no_geometry");

    group_by_term %= value_expression | column_reference;
    group_by_term.name("group_by_term");

    group_by %= lexeme[ascii::no_case["GROUP"] > &boost::spirit::qi::space] >
                lexeme[ascii::no_case["BY"] > &boost::spirit::qi::space] >
                (group_by_term % ',');
    group_by.name("group by");

    having %= lexeme[ascii::no_case["HAVING"] > &boost::spirit::qi::space] >
              search_condition;
    having.name("having");

    sort_key %= column_reference | unsigned_integer;

    ordering_specification %= ascii::no_case[ascii::string("ASC")] |
                              ascii::no_case[ascii::string("DESC")];
    // I have the vague feeling that there are cases where there are
    // no spaces between the sort_key and ordering_specification, but
    // I can not think of any.
    sort_specification %= sort_key >> -ordering_specification;
    order_by %= lexeme[ascii::no_case["ORDER"] > &boost::spirit::qi::space] >>
                lexeme[ascii::no_case["BY"] > &boost::spirit::qi::space] >>
                (sort_specification % ',');
    order_by.name("order by");

    // The expectation operator messes up the automatic calculation of
    // semantic actions.  So instead of %=, we have to do it manually
    // with [at_c<>(_val)=_1]

    select = lexeme[ascii::no_case["SELECT"] > &boost::spirit::qi::space] >>
             -set_quantifier[at_c<0>(_val) = _1] >>
             -(hold[lexeme[ascii::no_case["TOP"] >> &boost::spirit::qi::space]] >
               lexeme[ulong_long > &boost::spirit::qi::space])[at_c<1>(_val) = _1] >
             columns[at_c<2>(_val) = _1];
    select.name("select");

    select_from_where = select[at_c<0>(_val) = _1] > from_clause[at_c<1>(_val) = _1] >>
                        -where[at_c<2>(_val) = _1];

    select_from_where.name("select_from_where");

    // JTODO UNION ALL
    select_from_where_list = select_from_where % ascii::no_case[ascii::string("UNION")];
    select_from_where_list.name("select_from_where_list");

    select_from_where_no_geometry = select[at_c<0>(_val) = _1] >
                                    from_clause[at_c<1>(_val) = _1] >>
                                    -where_no_geometry[at_c<2>(_val) = _1];

    select_from_where_no_geometry.name("select_from_where_no_geometry");

    // Allow only a single element in the list (used to define subquery).
    select_from_where_no_geometry_list = select_from_where_no_geometry;
    select_from_where_no_geometry_list.name("select_from_where_no_geometry_list");

    query = -with[at_c<0>(_val) = _1] >> select_from_where_list[at_c<1>(_val) = _1] >>
            -group_by[at_c<2>(_val) = _1] >> -having[at_c<3>(_val) = _1] >>
            -order_by[at_c<4>(_val) = _1];
    query.name("query");

    query_no_geometry = -with[at_c<0>(_val) = _1] >>
                        select_from_where_no_geometry_list[at_c<1>(_val) = _1] >>
                        -group_by[at_c<2>(_val) = _1] >> -having[at_c<3>(_val) = _1] >>
                        -order_by[at_c<4>(_val) = _1];
    query_no_geometry.name("query_no_geometry");

    subquery %= lit('(') >> (query_no_geometry | joined_table) >> lit(')');
    subquery.name("subquery");

    boost::spirit::qi::on_error<boost::spirit::qi::fail>(
            query, boost::phoenix::ref((std::ostream &)error_stream)
                           << boost::phoenix::val("Error: Expecting ")
                           << boost::spirit::qi::labels::_4
                           << boost::phoenix::val(" here: \"")
                           << boost::phoenix::construct<std::string>(_3, _2)
                           << boost::phoenix::val("\"") << std::endl);

#ifdef DEBUG_Q
    BOOST_SPIRIT_DEBUG_NODE(where);
    BOOST_SPIRIT_DEBUG_NODE(where_no_geometry);
    BOOST_SPIRIT_DEBUG_NODE(group_by_term);
    BOOST_SPIRIT_DEBUG_NODE(group_by);
    BOOST_SPIRIT_DEBUG_NODE(having);
    BOOST_SPIRIT_DEBUG_NODE(select);
    BOOST_SPIRIT_DEBUG_NODE(select_from_where);
    BOOST_SPIRIT_DEBUG_NODE(select_from_where_list);
    BOOST_SPIRIT_DEBUG_NODE(order_by);
    BOOST_SPIRIT_DEBUG_NODE(query);
    BOOST_SPIRIT_DEBUG_NODE(query_no_geometry);
    BOOST_SPIRIT_DEBUG_NODE(subquery);
    BOOST_SPIRIT_DEBUG_NODE(with);
    BOOST_SPIRIT_DEBUG_NODE(with_table_name);
    BOOST_SPIRIT_DEBUG_NODE(with_column_name);
#endif
}
