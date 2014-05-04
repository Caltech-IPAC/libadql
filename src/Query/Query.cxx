#include "../Query.hxx"
#include "ADQL_parser.hxx"

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

  if(!where.geometry.empty())
    {
      std::string &ra(where.geometry.contains.point.coordinate.ra),
        &dec(where.geometry.contains.point.coordinate.dec);
      if (!(ra=="ra" || ra==table + ".ra"))
        throw std::runtime_error ("Invalid value for ra in Contains():\n\t"
                                  + ra);

      if (!(dec=="dec" || dec==table + ".dec"))
        throw std::runtime_error ("Invalid value for dec in Contains():\n\t"
                                  + dec);
      // FIXME: Check for valid numbers in the circle, box, etc.
    }
}
