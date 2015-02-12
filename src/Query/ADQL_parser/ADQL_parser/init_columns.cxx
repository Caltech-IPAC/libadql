#include "../../ADQL_parser.hxx"

void ADQL_parser::init_columns()
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
  term %= factor >> -(char_ ("*/") >> term);
  numeric_value_expression %= term
    >> -(char_ ("+-") >> numeric_value_expression);
  numeric_value_expression.name ("numeric_value_expression");

  // FIXME: string_value_function should have a string_geometry_function;
  string_value_function %= user_defined_function;
  /// Flipped the order here because a value_expression_primary can
  /// match a function name that should be matched by
  /// string_value_function
  character_primary %= string_value_function | value_expression_primary;
  character_factor %= character_primary;
  concatenation_operator %= ascii::string ("||");
  /// Flip the order of character_factor and
  /// character_value_expression to prevent recursion.
  character_value_expression
    %= character_factor
    >> -(concatenation_operator >> character_value_expression);

  string_value_expression %= character_value_expression;
  // FIXME: value_expression should also have a
  // geometry_value_expression, but the database can not handle it.

  /// This expression first checks for a concatenation operator.
  /// Otherwise a numeric_value_expression would match the first
  /// half of a concatenation, meaning the concatenation operator
  /// would cause the parse to fail.  We can not put
  /// string_value_expression first, because that would partially
  /// match arithmetic.  For 'a+b', it matches 'a' but not the '+'.
  value_expression %= (hold[character_factor >> concatenation_operator]
                       >> character_value_expression)
    | numeric_value_expression | string_value_expression;
  value_expression.name ("value_expression");

  column_name %= identifier;

  as %= value_expression
    >> lexeme[ascii::no_case["AS"] > &boost::spirit::qi::space]
    >> column_name;

  select_non_as_item %= hold[qualifier >> ascii::string (".*")]
    | value_expression;
  select_item %= as | select_non_as_item;
  select_list %= select_item % ',';
  columns %= ascii::string ("*") | select_list;
  columns.name ("columns");
}
