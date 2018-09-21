#include "../../ADQL_parser.hxx"

using boost::spirit::qi::hold;
using boost::spirit::qi::lexeme;
namespace ascii = boost::spirit::ascii;

void ADQL_parser::init_non_predicate_geometry_function ()
{

  geo_one_arg_names %= ascii::no_case[ascii::string ("COORD1")]
                     | ascii::no_case[ascii::string ("COORD2")];

  non_predicate_geometry_function %= (hold[lexeme[geo_one_arg_names >> &nonidentifier_character]]
                                      > '(' > point_or_column > ')');

  non_predicate_geometry_function.name ("non_predicate_geometry_function");

}
