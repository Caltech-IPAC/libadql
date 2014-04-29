#include "../Query.hxx"
#include "ADQL_parser.hxx"
#include "Check_RA_DEC.hxx"

ADQL::Query::Query (const std::string &input):
  top(std::numeric_limits<unsigned long long>::max())
{
  ADQL_parser<std::string::const_iterator> parser;
  std::string::const_iterator begin (input.begin ()), end (input.end ());

  bool valid (
      phrase_parse (begin, end, parser, boost::spirit::ascii::space, *this));

  if (!(valid && begin == end))
    {
      throw std::runtime_error ("");
    }

  if(where.geometry.good())
    {
      if (!boost::apply_visitor (Check_RA_DEC (table, "ra"),
                                 where.geometry.contains.point.coordinate.numbers[0]))
        throw std::runtime_error ("Invalid value for ra in Contains():\n\t");

      if (!boost::apply_visitor (Check_RA_DEC (table, "dec"),
                                 where.geometry.contains.point.coordinate.numbers[1]))
        throw std::runtime_error ("Invalid value for dec in Contains():\n\t");
    }
}
