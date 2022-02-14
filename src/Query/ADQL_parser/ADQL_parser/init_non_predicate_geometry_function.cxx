#include "../../ADQL_parser.hxx"

using boost::spirit::qi::hold;
using boost::spirit::qi::lexeme;
namespace ascii = boost::spirit::ascii;

void ADQL_parser::init_non_predicate_geometry_function() {
    geo_one_arg_names %= ascii::no_case[ascii::string("COORD1")] |
                         ascii::no_case[ascii::string("COORD2")];

    geo_two_arg_names %= ascii::no_case[ascii::string("DISTANCE")];

    non_predicate_geometry_function_one_arg %=
            (hold[lexeme[geo_one_arg_names >> &nonidentifier_character]] > '(' >
             point_or_column > ')');

    non_predicate_geometry_function_two_arg %=
            (hold[lexeme[geo_two_arg_names >> &nonidentifier_character]] > '(' >
             point_or_column > ',' > point_or_column > ')');

    non_predicate_geometry_function %= non_predicate_geometry_function_one_arg |
                                       non_predicate_geometry_function_two_arg;

    non_predicate_geometry_function.name("non_predicate_geometry_function");

#ifdef DEBUG_NON_PRED
    BOOST_SPIRIT_DEBUG_NODE(non_predicate_geometry_function);
#endif
}
