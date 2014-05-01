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
    using boost::spirit::qi::ulong_long;
    using boost::spirit::qi::hold;
    using boost::spirit::qi::lower;
    using boost::spirit::qi::omit;
    using boost::spirit::qi::print;
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

    period %= char_('.');

    catalog_name %= identifier;
    unqualified_schema_name %= identifier;
    schema_name %= -(hold[catalog_name >> period]) >> unqualified_schema_name;
    table_name %= -(hold[schema_name >> period]) >> identifier;
    correlation_name %= identifier;

    /// Only use table_name, since as the rules are written
    /// correlation_name will never match.
    qualifier %= table_name;
    // qualifier %= correlation_name | table_name;

    column_reference %= -(hold[qualifier >> period]) >> identifier;

    unsigned_integer %= +digit;
    exact_numeric_literal %= (unsigned_integer
                              >> -(period >> unsigned_integer))
      | (period >> unsigned_integer);

    sign %= char_('+') | char_('-');
    signed_integer %= -sign >> unsigned_integer;
    mantissa %= exact_numeric_literal;
    exponent %= signed_integer;
    approximate_numeric_literal %= mantissa >> char_('E') >> exponent;
    unsigned_numeric_literal %= 
      exact_numeric_literal | approximate_numeric_literal;


    quote %= char_('\'');
    space %= char_(' ');
    newline %= char_('\n');
    minus_sign %= char_('-');

    // FIXME: The ADQL spec is not clear about exactly what this is.
    // Does it include spaces and newlines?
    nonquote_character %= print - quote;
    quote_symbol %= quote >> quote;
    character_representation %= nonquote_character | quote_symbol;

    comment_introducer %= minus_sign >> +minus_sign;
    comment_character %= nonquote_character | quote;
    comment %= comment_introducer >> *comment_character >> newline;

    separator %= comment | space | newline;
    
    character_string_literal %=
      quote >> *character_representation >> quote
            >> -(+separator >> quote >> *character_representation >> quote);

    general_literal %= character_string_literal;
    unsigned_literal %= unsigned_numeric_literal | general_literal;
    unsigned_value_specification %= unsigned_literal;

    set_function_type %= ascii::no_case[ascii::string("AVG")]
      | ascii::no_case[ascii::string("MAX")]
      | ascii::no_case[ascii::string("MIN")]
      | ascii::no_case[ascii::string("SUM")]
      | ascii::no_case[ascii::string("COUNT")];
    set_quantifier %=ascii::no_case[ascii::string("DISTINCT")]
      | ascii::no_case[ascii::string("ALL")];

    general_set_function %= set_function_type
      >> char_('(') >> -set_quantifier >> value_expression >> char_(')');

    set_function_specification %=
      (ascii::no_case[ascii::string("COUNT")]
       >> char_('(') >> char_('*') >> char_(')'))
      | general_set_function;

    value_expression_primary %=
      unsigned_value_specification
      | column_reference
      | set_function_specification
      | (char_('(') >> value_expression >> char_(')'));


    trig_function %=
      ((ascii::no_case[ascii::string("ACOS")]
        | ascii::no_case[ascii::string("ASIN")]
        | ascii::no_case[ascii::string("ATAN")]
        | ascii::no_case[ascii::string("COS")]
        | ascii::no_case[ascii::string("COT")]
        | ascii::no_case[ascii::string("SIN")]
        | ascii::no_case[ascii::string("TAN")])
       >> char_('(')
       >> numeric_value_expression >> char_(')'))
      | (ascii::no_case[ascii::string("ATAN2")]
         >> char_('(')
         >> numeric_value_expression
         >> char_(',')
         >> numeric_value_expression
         >> char_(')'));

    math_function %= 
      ((ascii::no_case[ascii::string("ABS")]
        | ascii::no_case[ascii::string("CEILING")]
        | ascii::no_case[ascii::string("DEGREES")]
        | ascii::no_case[ascii::string("EXP")]
        | ascii::no_case[ascii::string("FLOOR")]
        | ascii::no_case[ascii::string("LOG10")]
        | ascii::no_case[ascii::string("LOG")]
        | ascii::no_case[ascii::string("RADIANS")]
        | ascii::no_case[ascii::string("SQRT")])
       >> char_('(')
       >> numeric_value_expression >> char_(')'))
      | ((ascii::no_case[ascii::string("MOD")]
          | ascii::no_case[ascii::string("POWER")])
         >> char_('(')
         >> numeric_value_expression
         >> char_(',')
         >> numeric_value_expression
         >> char_(')'))
      | (ascii::no_case[ascii::string("PI")]
         >> char_('(')
         >> char_(')'))
      | (ascii::no_case[ascii::string("RAND")]
         >> char_('(')
         >> -numeric_value_expression >> char_(')'))
      | ((ascii::no_case[ascii::string("ROUND")]
          | ascii::no_case[ascii::string("TRUNCATE")])
         >> char_('(')
         >> numeric_value_expression
         >> -(char_(',') >> signed_integer)
         >> char_(')'));

    numeric_value_function %= trig_function | math_function;
    /// Flipped the order here, because a value_expression can match SIN.
    numeric_primary %= numeric_value_function | value_expression_primary;
    factor %= -sign >> numeric_primary;

    /// This puts term and numeric_value_expression on the left, not
    /// right.  Otherwise the rule greedily recurses on itself and
    /// runs out of stack space.  Then the first term is always the
    /// same and the second part becomes optional.
    term %= factor >> -(char_("*/") >> term);
    numeric_value_expression %=
      term >> -(char_("+-") >> numeric_value_expression);

    // FIXME: value_expression should also have a
    // geometry_value_expression, but the database can not handle it.
    value_expression %=
      numeric_value_expression;
    // value_expression %=
    //   numeric_value_expression
    //   | string_value_expression;

    coord %= numeric_value_expression >> ',' >> numeric_value_expression;
    point %= ascii::no_case["POINT("] >> coord_sys >> ',' >> coord >> ')';

    circle %= ascii::no_case["CIRCLE("] >> coord_sys >> ',' >> coord >> ','
              >> boost::spirit::qi::double_ >> ')';

    contains %= ascii::no_case["CONTAINS("] >> point >> ',' >> circle >> ')';

    geometry %= (contains >> '=' >> '1') | (lit('1') >> '=' >> contains);

    column_name %=identifier;
    as %= value_expression >> ascii::no_case["AS"] >> column_name;

    select_item %= as | (hold[qualifier >> ascii::string(".*")]
                         | value_expression);
    select_list %= select_item % ',';
    columns %= ascii::string("*") | select_list;

    comparison_predicate %= value_expression
      >> (ascii::string("=") | ascii::string("!=") | ascii::string("<>")
          | ascii::string("<") | ascii::string("<=") | ascii::string(">")
          | ascii::string(">="))
      >> value_expression;

    between_predicate %= value_expression
      >> -ascii::no_case[ascii::string("NOT")]
      >> ascii::no_case["BETWEEN"]
      >> value_expression
      >> ascii::no_case["AND"] >> value_expression; 

    in_predicate %= value_expression
      >> -ascii::no_case[ascii::string("NOT")]
      >> ascii::no_case["IN"]
    // FIXME: This should be table_subquery, not value_expression
      >> (value_expression
          | (lit('(') >> (value_expression % ',') >> ')'));

    predicate %= (comparison_predicate | between_predicate | in_predicate);

    boolean_primary %= predicate | (lit('(') >> search_condition >> ')');

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
           >> -(ascii::no_case["AND"] >> '('
                >> search_condition[at_c<1>(_val)=_1]
                >> ')'))
          | (lit('(') >> search_condition[at_c<1>(_val)=_1] >> ')'
             >> (ascii::no_case["AND"] >> geometry[at_c<0>(_val)=_1]))
          | (search_condition[at_c<1>(_val)=_1]));


    query %= ascii::no_case["SELECT"]
      >> -set_quantifier
      >> -(ascii::no_case["TOP"] >> ulong_long)
      >> columns
      >> ascii::no_case["FROM"]
      >> identifier
      >> (-where);
  }

  boost::spirit::qi::rule<Iterator, char()> simple_Latin_letter;

  boost::spirit::qi::rule<Iterator, std::string ()> regular_identifier,
    identifier, column_reference, qualifier, correlation_name,
    table_name, schema_name, unqualified_schema_name, catalog_name, sign,
    period, unsigned_integer, exact_numeric_literal, signed_integer, mantissa,
    exponent, approximate_numeric_literal, unsigned_numeric_literal,
    quote, nonquote_character, quote_symbol, character_representation,
    space, newline, minus_sign, comment_introducer, comment_character,
    comment, separator, character_string_literal, general_literal,
    unsigned_literal, unsigned_value_specification,
    set_function_type, set_quantifier, general_set_function,
    set_function_specification,
    value_expression_primary, value_expression,
    numeric_value_expression, numeric_primary, factor, term,
    numeric_value_function, trig_function, math_function;

  boost::spirit::qi::rule<Iterator, ADQL::Coord_Sys (),
                          boost::spirit::ascii::space_type> coord_sys;
  boost::spirit::qi::rule<Iterator, ADQL::Coordinate (),
                          boost::spirit::ascii::space_type> coord;

  boost::spirit::qi::rule<Iterator, std::string(),
                          boost::spirit::ascii::space_type> column_name;

  boost::spirit::qi::rule<Iterator, ADQL::Query::Column_Variant (),
                          boost::spirit::ascii::space_type> select_item;

  boost::spirit::qi::rule<Iterator, std::vector<ADQL::Query::Column_Variant> (),
                          boost::spirit::ascii::space_type> select_list;

  boost::spirit::qi::rule<Iterator, ADQL::Query::Columns (),
                          boost::spirit::ascii::space_type> columns;

  boost::spirit::qi::rule<Iterator, ADQL::As (),
                          boost::spirit::ascii::space_type> as;

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

  boost::spirit::qi::rule<Iterator, ADQL::In_Predicate (),
                          boost::spirit::ascii::space_type> in_predicate;

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
