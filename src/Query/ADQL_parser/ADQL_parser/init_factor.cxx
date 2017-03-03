#include "../../ADQL_parser.hxx"

void ADQL_parser::init_factor()
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

  set_function_type %= ascii::no_case[ascii::string ("AVG")]
    | ascii::no_case[ascii::string ("MAX")]
    | ascii::no_case[ascii::string ("MIN")]
    | ascii::no_case[ascii::string ("SUM")]
    | ascii::no_case[ascii::string ("COUNT")];
  /// This is a little funky because we need to preserve the space
  /// between the set_quantifier and whatever follows it.
  set_quantifier %= hold[lexeme[(ascii::no_case[ascii::string ("DISTINCT")]
                                 | ascii::no_case[ascii::string ("ALL")])
                                >> &boost::spirit::qi::space]];

  general_set_function %= (hold[lexeme[set_function_type
                                       >> &nonidentifier_character]]
                           > char_ ('(')) >> -set_quantifier
    > value_expression > char_ (')');

  set_function_specification
    %= (hold[ascii::no_case[ascii::string ("COUNT")] >> char_ ('(')
             >> char_ ('*')] > char_ (')')) | general_set_function;

  /// The BNF for SQL 99 uses an array_element_reference intermediate
  /// rule.  However, that rule first checks for value_expression, so
  /// you get an infinite recursion because it keeps matching the
  /// value_expression part of the array element.  So instead we
  /// implement array elements as optional decorators after an expression.
  value_expression_primary
    %= (array_value_constructor_by_enumeration
        | unsigned_value_specification | column_reference_string
        | set_function_specification
        | hold[char_ ('(') >> value_expression >> char_ (')')])
    >> *(char_ ('[') >> numeric_value_expression >> char_ (']'));

  trig_function
    %= (hold[lexeme[(ascii::no_case[ascii::string ("ACOS")]
              | ascii::no_case[ascii::string ("ASIN")]
              | ascii::no_case[ascii::string ("ATAN")]
              | ascii::no_case[ascii::string ("COS")]
              | ascii::no_case[ascii::string ("COT")]
              | ascii::no_case[ascii::string ("SIN")]
              | ascii::no_case[ascii::string ("TAN")])
             >> &nonidentifier_character]] > char_ ('(')
        > numeric_value_expression > char_ (')'))
    | (hold[lexeme[ascii::no_case[ascii::string ("ATAN2")]
                   >> &nonidentifier_character]]
       > char_ ('(')
       > numeric_value_expression > char_ (',')
       > numeric_value_expression > char_ (')'));

  math_function
    %= (hold[lexeme[(ascii::no_case[ascii::string ("ABS")]
                     | ascii::no_case[ascii::string ("CEILING")]
                     | ascii::no_case[ascii::string ("DEGREES")]
                     | ascii::no_case[ascii::string ("EXP")]
                     | ascii::no_case[ascii::string ("FLOOR")]
                     | ascii::no_case[ascii::string ("LOG10")]
                     | ascii::no_case[ascii::string ("LOG")]
                     | ascii::no_case[ascii::string ("RADIANS")]
                     | ascii::no_case[ascii::string ("SQRT")])
                    >> &nonidentifier_character]] > char_ ('(')
        > numeric_value_expression > char_ (')'))
    | (hold[lexeme[(ascii::no_case[ascii::string ("MOD")]
                    | ascii::no_case[ascii::string ("POWER")])
                   >> &nonidentifier_character]] > char_ ('(')
       > numeric_value_expression > char_ (',')
       > numeric_value_expression > char_ (')'))
    | (hold[lexeme[ascii::no_case[ascii::string ("PI")]
                   >> &nonidentifier_character]] > char_ ('(')
       > char_ (')'))
    | (hold[lexeme[ascii::no_case[ascii::string ("RAND")]
                   >> &nonidentifier_character]] > char_ ('(')
       >> -numeric_value_expression > char_ (')'))
    | (hold[lexeme[(ascii::no_case[ascii::string ("ROUND")]
                    | ascii::no_case[ascii::string ("TRUNCATE")])
                   >> &nonidentifier_character]]
       > char_ ('(') > numeric_value_expression
       >> -(char_ (',') > signed_integer) > char_ (')'));

  /// default_function_prefix is a bit useless since it is optional.
  default_function_prefix %= ascii::string ("udf_");
  /// Add RIGHT and LEFT as possible function names since they are
  /// normally reserved words, but also really useful Postgres string
  /// functions.
  user_defined_function_name %= -default_function_prefix
    >> (regular_identifier | ascii::no_case[ascii::string ("RIGHT")]
        | ascii::no_case[ascii::string ("LEFT")]);
  user_defined_function_param %= value_expression;
  user_defined_function
    %= hold[user_defined_function_name >> char_ ('(')]
    /// Use this awkward syntax instead of the usual list parser so
    /// that the attribute is still a string overall.
    >> -(user_defined_function_param
         >> *(char_ (',') >> user_defined_function_param))
    >> char_ (')');

  // FIXME: numeric_value_function should have
  // numeric_geometry_function
  numeric_value_function %= trig_function | math_function
    | user_defined_function;
  /// Flipped the order here, because a value_expression can match a
  /// function name.
  numeric_primary %= numeric_value_function | value_expression_primary;
  factor %= -sign >> numeric_primary;
}
