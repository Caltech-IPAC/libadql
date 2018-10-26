#include <boost/spirit/include/phoenix_bind.hpp>

#include "../../ADQL_parser.hxx"

void ADQL_parser::init_correlation_specification ()
{
  using boost::spirit::qi::lexeme;
  namespace ascii = boost::spirit::ascii;

  correlation_name %= identifier;

  correlation_specification
      %= -lexeme[ascii::no_case["AS"] >> &boost::spirit::qi::space]
         >> correlation_name;
  correlation_specification.name ("correlation_specification");
}
