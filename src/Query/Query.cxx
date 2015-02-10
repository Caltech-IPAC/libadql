#include "../Query.hxx"
#include "ADQL_parser.hxx"

ADQL::Query::Query (const std::string &input, const std::map<std::string,std::string> &table_mapping)
    : top (std::numeric_limits<unsigned long long>::max ())
{
  ADQL_parser<std::string::const_iterator> parser(table_mapping);
  std::string::const_iterator begin (input.begin ()), end (input.end ());

  bool valid (
      phrase_parse (begin, end, parser, boost::spirit::ascii::space, *this));

  if (!(valid && begin == end))
    {
      auto error=parser.error_stream.str ();
      if (error.empty ())
        error="Expecting <SELECT> here: \"" + input + "\"";;
      throw std::runtime_error (error);
    }
}
