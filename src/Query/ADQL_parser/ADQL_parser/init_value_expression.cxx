#include "../../ADQL_parser.hxx"

void ADQL_parser::init_value_expression ()
{
  namespace ascii = boost::spirit::ascii;

  // FIXME: value_expression should also have a
  // geometry_value_expression, but the database can not handle it.

  /// Since we are not evaluating the expression, we do not care all
  /// that much about operator precedence.  So put all of the binary
  /// operators into a single term.
  binary_operators
      %= ascii::string ("*") | ascii::string ("/") | ascii::string ("+")
         | ascii::string ("-") | ascii::string ("||");
  value_expression_non_bool_term %= binary_operators >> factor;
  value_expression_non_bool %= factor >> *value_expression_non_bool_term;
  value_expression_non_bool.name ("value_expression_non_bool");

  value_expression %= value_expression_non_bool | boolean_value_expression;
  value_expression.name ("value_expression");

}
