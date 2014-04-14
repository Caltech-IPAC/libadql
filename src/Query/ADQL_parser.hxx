#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"

#include "../Query.hxx"

template <typename Iterator>
struct ADQL_parser
    : boost::spirit::qi::grammar<Iterator, ADQL::Query (),
                                 boost::spirit::ascii::space_type>
{
  ADQL_parser () : ADQL_parser::base_type (query)
  {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::labels::_val;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::alpha;
    using boost::spirit::qi::alnum;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::hold;
    using boost::spirit::qi::lower;
    using boost::spirit::qi::omit;
    namespace ascii=boost::spirit::ascii;

    simple_Latin_letter %= char_ ("a-zA-Z");
    regular_identifier %= simple_Latin_letter
                          >> *(digit | simple_Latin_letter | char_ ("_"));

    // FIXME: add delimited identifier
    identifier %= regular_identifier;

    coord_sys
      %= '\'' >> -ascii::no_case["J2000"][at_c<0>(_val)
                                  = ADQL::Coord_Sys::Reference_Frame::J2000] 
                >> -ascii::no_case["GEOCENTER"][at_c<1>(_val)
                              = ADQL::Coord_Sys::Reference_Position::GEOCENTER]
                >> '\'';

    catalog_name %= identifier;
    unqualified_schema_name %= identifier;
    schema_name = -(catalog_name >> char_ ("."))[_val = _1 + _2]
                  >> unqualified_schema_name[_val += _1];
    table_name = -(schema_name >> char_ ("."))[_val = _1 + _2]
                 >> identifier[_val += _1];
    correlation_name %= identifier;

    qualifier %= hold[table_name] | correlation_name;

    column_reference = -(qualifier >> char_ ("."))[_val = _1 + _2]
                       >> identifier[_val += _1];

    number %= double_;

    // FIXME: Add functions etc. into factor
    factor %= number | column_reference;

    // FIXME: add math (*/) into term
    term %= factor;

    // FIXME: add math (+-) into numeric_value_expression
    numeric_value_expression %= term;

    coord %= numeric_value_expression >> ',' >> numeric_value_expression;
    point %= ascii::no_case["POINT("] >> coord_sys >> "," >> coord >> ")";

    circle %= ascii::no_case["CIRCLE("] >> coord_sys >> "," >> coord >> ','
              >> boost::spirit::qi::double_ >> ")";

    contains %= ascii::no_case["CONTAINS("] >> point >> "," >> circle >> ")";

    geometry %= (contains >> "=" >> "1") | (lit("1") >> "=" >> contains);

    as %= identifier >> ascii::no_case["AS"] >> identifier;

    column_name %=identifier | char_ ("*");

    select_item %= as | column_name;

    comparison_predicate %= numeric_value_expression
      >> (ascii::string("==") | ascii::string("!=") | ascii::string("<>")
          | ascii::string("<") | ascii::string("<=") | ascii::string(">")
          | ascii::string(">="))
      >> numeric_value_expression;

    between_predicate %= numeric_value_expression
      >> -ascii::no_case[ascii::string("NOT")]
      >> ascii::no_case["BETWEEN"]
      >> numeric_value_expression
      >> ascii::no_case["AND"] >> numeric_value_expression; 

    predicate %= (comparison_predicate | between_predicate);

    boolean_primary %= predicate | (lit("(") >> search_condition >> ")");

    boolean_factor %= -ascii::no_case[ascii::string("NOT")]
      >> boolean_primary;

    boolean_term %= boolean_factor
      >> (ascii::no_case[ascii::string("AND")]
          | ascii::no_case[ascii::string("OR")])
      >> search_condition;

    search_condition =
      (boolean_term | boolean_factor)[push_back(at_c<0>(_val), _1)];

    where = ascii::no_case["WHERE"]
      >> ((geometry[at_c<0>(_val)=_1]
           >> -(ascii::no_case["AND"] >> search_condition[at_c<1>(_val)=_1]))
           | (search_condition[at_c<1>(_val)=_1]
              >> -(ascii::no_case["AND"] >> geometry[at_c<0>(_val)=_1])));

    query %= ascii::no_case["SELECT"]
      >> (select_item % ',')
      >> ascii::no_case["FROM"]
      >> identifier
      >> (-where);
  }

  boost::spirit::qi::rule<Iterator, char()> simple_Latin_letter;

  boost::spirit::qi::rule<Iterator, std::string ()> regular_identifier,
      identifier, column_reference, qualifier, correlation_name,
      table_name, schema_name, unqualified_schema_name, catalog_name, sign,
      unsigned_integer, signed_integer, exponent, exact_numeric_literal;

  boost::spirit::qi::rule<Iterator, ADQL::Coord_Sys (),
                          boost::spirit::ascii::space_type> coord_sys;
  boost::spirit::qi::rule<Iterator, ADQL::Coordinate (),
                          boost::spirit::ascii::space_type> coord;

  boost::spirit::qi::rule<Iterator, std::string(),
                          boost::spirit::ascii::space_type> column_name;

  boost::spirit::qi::rule<Iterator, ADQL::column_variant (),
                          boost::spirit::ascii::space_type> select_item;

  boost::spirit::qi::rule<Iterator, ADQL::As (),
                          boost::spirit::ascii::space_type> as;

  boost::spirit::qi::rule<Iterator, ADQL::Number_Variant (),
                          boost::spirit::ascii::space_type>
  numeric_value_expression, factor, term;

  boost::spirit::qi::rule<Iterator, double(), boost::spirit::ascii::space_type>
  number;

  boost::spirit::qi::rule<Iterator, ADQL::Point (),
                          boost::spirit::ascii::space_type> point;
  boost::spirit::qi::rule<Iterator, ADQL::Circle (),
                          boost::spirit::ascii::space_type> circle;

  boost::spirit::qi::rule<Iterator, ADQL::Contains (),
                          boost::spirit::ascii::space_type> contains;

  boost::spirit::qi::rule<Iterator, ADQL::Geometry (),
                          boost::spirit::ascii::space_type> geometry;

  boost::spirit::qi::rule<Iterator, ADQL::Comparison_Predicate (),
                          boost::spirit::ascii::space_type> comparison_predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Between_Predicate (),
                          boost::spirit::ascii::space_type> between_predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Predicate (),
                          boost::spirit::ascii::space_type> predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Boolean_Primary (),
                          boost::spirit::ascii::space_type> boolean_primary;

  boost::spirit::qi::rule<Iterator, ADQL::Boolean_Factor (),
                          boost::spirit::ascii::space_type> boolean_factor;

  boost::spirit::qi::rule<Iterator, ADQL::Boolean_Term (),
                          boost::spirit::ascii::space_type> boolean_term;

  boost::spirit::qi::rule<Iterator, ADQL::Search_Condition (),
                          boost::spirit::ascii::space_type> search_condition;

  boost::spirit::qi::rule<Iterator, ADQL::Where (),
                          boost::spirit::ascii::space_type> where;

  boost::spirit::qi::rule<Iterator, ADQL::Query (),
                          boost::spirit::ascii::space_type> query;
};
