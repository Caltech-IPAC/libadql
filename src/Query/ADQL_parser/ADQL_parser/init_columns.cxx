#include "../../ADQL_parser.hxx"

void ADQL_parser::init_columns ()
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
  using boost::spirit::qi::lexeme;
  using boost::spirit::qi::no_skip;
  namespace ascii = boost::spirit::ascii;

  /// This puts term and numeric_value_expression on the left, not
  /// right.  Otherwise the rule greedily recurses on itself and
  /// runs out of stack space.  With that reordering, the first term
  /// is always the same and the second part becomes optional.

  operator_term %= factor >> char_ ("*/") >> term;
  term %= operator_term | factor;
  operator_numeric_value_expression %= term >> char_ ("+-")
                                       >> numeric_value_expression;
  numeric_value_expression %= operator_numeric_value_expression | term;

  /// Flipped the order here because a value_expression_primary can
  /// match a function name that should be matched by
  /// string_value_function

  character_factor %= user_defined_function | value_expression_primary;
  character_value_expression %= character_factor % "||";
  string_value_expression %= character_value_expression;

  // FIXME: value_expression should also have a
  // geometry_value_expression, but the database can not handle it.

  /// string_value_expression will stop short at any non-concatenation
  /// operation but still consume the input.  Similarly,
  /// numeric_value_expression will stop short at concatenation but
  /// still consume the input.  So we add concatenation_expression,
  /// which requires concatenation, to break this degeneracy.

  concatenation_expression %= hold[character_factor >> "||"]
                              >> (character_factor % "||");

  value_expression_non_bool %= concatenation_expression
                               | numeric_value_expression
                               | string_value_expression;
  value_expression_non_bool.name ("value_expression_non_bool");

  value_expression %= value_expression_non_bool | boolean_value_expression;
  value_expression.name ("value_expression");

  column_name %= identifier;
  column_name.name ("column_name");

  as = value_expression[at_c<0>(_val) = _1]
       >> lexeme[ascii::no_case["AS"] >> &boost::spirit::qi::space]
       > column_name[at_c<1>(_val) = _1];
  as.name ("as");
  
  qualifier_star %= qualifier >> ascii::string (".*");
  non_as %= qualifier_star | value_expression;
  non_as.name ("non_as");
  select_item %= as | non_as;
  select_list %= select_item % ',';
  columns %= ascii::string ("*") | select_list;
  columns.name ("columns");
}
