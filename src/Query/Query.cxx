#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"

#include "../Query.hxx"

namespace
{
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

    simple_Latin_letter %= char_ ("a-zA-Z");
    regular_identifier %= simple_Latin_letter
                          >> *(digit | simple_Latin_letter | char_ ("_"));

    // FIXME: add delimited identifier
    identifier %= regular_identifier;

    coord_sys
        %= '\'' >> -lit ("J2000")[at_c<0>(_val)
                                  = ADQL::Coord_Sys::Reference_Frame::J2000]
           >> -lit (
                 "GEOCENTER")[at_c<1>(_val)
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
    point %= "POINT(" >> coord_sys >> "," >> coord >> ")";

    circle %= "CIRCLE(" >> coord_sys >> "," >> coord >> ','
              >> boost::spirit::qi::double_ >> ")";

    contains %= "CONTAINS(" >> point >> "," >> circle >> ")";

    geometry %= contains;

    column_name %= identifier | char_ ("*");

    query = lit ("SELECT") >> ((column_name % ',')[at_c<0>(_val) = _1])
            >> "FROM" >> (identifier[at_c<1>(_val) = _1]) >> "WHERE"
            >> (geometry[at_c<2>(_val) = _1]);
  }

  boost::spirit::qi::rule<Iterator, char()> simple_Latin_letter;

  boost::spirit::qi::rule<Iterator, std::string ()> regular_identifier,
      identifier, column_name, column_reference, qualifier, correlation_name,
      table_name, schema_name, unqualified_schema_name, catalog_name, sign,
      unsigned_integer, signed_integer, exponent, exact_numeric_literal;

  boost::spirit::qi::rule<Iterator, ADQL::Coord_Sys (),
                          boost::spirit::ascii::space_type> coord_sys;
  boost::spirit::qi::rule<Iterator, ADQL::Coordinate (),
                          boost::spirit::ascii::space_type> coord;

  boost::spirit::qi::rule<Iterator, ADQL::number_variant (),
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

  boost::spirit::qi::rule<Iterator, ADQL::Query (),
                          boost::spirit::ascii::space_type> query;
};

class Check_RA_DEC : public boost::static_visitor<bool>
{
  std::string table, ra_dec;

public:
  Check_RA_DEC (const std::string &Table, const std::string &Ra_dec)
      : table (Table), ra_dec (Ra_dec)
  {
  }
  bool operator()(const double &) const { return false; }
  bool operator()(const std::string &s) const
  {
    return s == ra_dec || s == table + "." + ra_dec;
  }
};
}

ADQL::Query::Query (const std::string &input)
{
  ADQL_parser<std::string::const_iterator> parser;
  std::string::const_iterator begin (input.begin ()), end (input.end ());

  bool valid (
      phrase_parse (begin, end, parser, boost::spirit::ascii::space, *this));

  if (!(valid && begin == end))
    {
      throw std::runtime_error ("");
    }

  if (!boost::apply_visitor (Check_RA_DEC (table, "ra"),
                             geometry.contains.point.coordinate.numbers[0]))
    throw std::runtime_error ("Invalid value for ra in Contains():\n\t");

  if (!boost::apply_visitor (Check_RA_DEC (table, "dec"),
                             geometry.contains.point.coordinate.numbers[1]))
    throw std::runtime_error ("Invalid value for dec in Contains():\n\t");
}
