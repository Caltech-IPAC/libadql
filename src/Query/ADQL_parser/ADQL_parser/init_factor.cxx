#include "../../ADQL_parser.hxx"

void ADQL_parser::init_factor ()
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
  set_function_type.name ("set_function_type");
  /// This is a little funky because we need to preserve the space
  /// between the set_quantifier and whatever follows it.
  set_quantifier %= hold[lexeme[(ascii::no_case[ascii::string ("DISTINCT")]
                                 | ascii::no_case[ascii::string ("ALL")])
                                >> &boost::spirit::qi::space]];
  set_quantifier.name ("set_quantifier");
  general_set_args = -set_quantifier >> value_expression;
  general_set_function %= set_function_type >> '(' > general_set_args > ')';
  general_set_function.name ("general_set_function");

  count_star %= ascii::no_case[ascii::string ("COUNT")] >> char_ ('(')
                >> char_ ('*') > char_ (')');
  set_function_specification %= count_star | general_set_function;
  set_function_specification.name ("set_function_specification");

  null_string %= ascii::no_case[ascii::string ("NULL")];
  result %= value_expression | null_string;
  result.name ("result");
  simple_when %= ascii::no_case["WHEN"] >> &no_skip[boost::spirit::qi::space]
    > value_expression >> ascii::no_case["THEN"]
                 > &no_skip[boost::spirit::qi::space] > result;
  simple_when.name ("simple_when_clause");

  simple_whens %= simple_when >> *simple_when;
  simple_whens.name ("simple_whens");

  else_clause %= ascii::no_case["ELSE"] >> &no_skip[boost::spirit::qi::space]
                 >> result;
  else_clause.name ("else_clause");

  /// boost::spirit gets wonky if I try to use the '>' operator for
  /// simple_whens
  simple_case %= value_expression >> simple_whens >> -else_clause
                 > ascii::no_case["END"];
  simple_case.name ("simple_case");

  // searched_when %= ascii::no_case[ascii::string ("WHEN")]
  //                  >> search_condition
  //                  >> ascii::no_case[ascii::string ("THEN")]
  //                  >> result;

  searched_case %= searched_when >> -else_clause
                   >> &no_skip[boost::spirit::qi::space]
                   >> ascii::no_case["END"];
  searched_case.name ("searched_case");
  
  case_specification %= ascii::no_case["CASE"]
                        >> &no_skip[boost::spirit::qi::space]
                        > (simple_case | searched_case);
  case_specification.name ("case_specification");

  nullif %= ascii::no_case["NULLIF"] >> '(' >> value_expression_string >> ','
            >> value_expression_string >> ')';
  nullif.name ("nullif");
  coalesce %= ascii::no_case["COALESCE"] >> '(' >> value_expression_string
              >> *(char_ (',') >> value_expression_string) >> ')';
  coalesce.name ("coalesce");
  case_abbreviation %= nullif | coalesce;
  case_abbreviation.name ("case_abbreviation");
  case_expression %= case_abbreviation | case_specification;
  case_expression.name ("case_expression");

  any_expression %= ascii::no_case["ANY"] >> '(' > value_expression > ')';
  any_expression.name ("any_expression");

  /// The BNF for SQL 99 uses an array_element_reference intermediate
  /// rule.  However, that rule first checks for value_expression, so
  /// you get an infinite recursion because it keeps matching the
  /// value_expression part of the array element.  So instead we
  /// implement array elements as optional decorators after an expression.

  value_subexpression %= hold['(' >> value_expression >> ')'];
  value_subexpression.name ("value_subexpression");

  array_index %= hold['[' >> numeric_value_expression >> ']'];
  array_index.name ("array_index");

  value_expression_primary
      %= (array_constructor | unsigned_value_specification | column_reference
          | set_function_specification | case_expression | any_expression
          | value_subexpression) >> *array_index;
  value_expression_primary.name ("value_expression_primary");

  /// Custom array_expression so that SQL 99 array literals can pass
  /// through
  array_constructor %= ascii::no_case["ARRAY"] >> '['
                       >> (value_expression % ',') > ']';
  array_constructor.name ("array_constructor");

  /// We do not have a rule for default_function_prefix since, being
  /// optional, it does not change whether something parses.

  /// Add a bunch of functions that are normally reserved words, but
  /// also really useful string functions (at least in Postgres)
  user_defined_function_name %= regular_identifier
                                | ascii::no_case[ascii::string ("RIGHT")]
                                | ascii::no_case[ascii::string ("LEFT")]
                                | ascii::no_case[ascii::string ("UPPER")]
                                | ascii::no_case[ascii::string ("LOWER")]
                                | ascii::no_case[ascii::string ("TRIM")];
  user_defined_function_name.name ("user_defined_function_name");
  user_defined_function_param %= value_expression;
  user_defined_function_param.name ("user_defined_function_param");

  user_defined_function %= hold[user_defined_function_name >> '(']
                           >> -(user_defined_function_param % ',') >> ')';

  user_defined_function.name ("user_defined_function");

  /// Special case casting to numeric, since some functions
  /// (e.g. mod()) only take numeric arguments, not double precision.

  cast_as %= ascii::no_case[ascii::string ("NUMERIC")]
             | ascii::no_case[ascii::string ("FLOAT4")]
             | ascii::no_case[ascii::string ("FLOAT8")];

  cast_function
      %= hold[ascii::no_case["CAST"] >> '(' >> value_expression
              >> &no_skip[boost::spirit::qi::space] >> ascii::no_case["AS"]
              >> &no_skip[boost::spirit::qi::space] >> cast_as >> ')'];
  cast_function.name ("cast_function");

  // FIXME: numeric_value_function should have
  // numeric_geometry_function
  numeric_value_function %= trig_function | math_function | cast_function
                            | user_defined_function;
  numeric_value_function.name ("numeric_value_function");
  /// Flipped the order here, because a value_expression can match a
  /// function name.
  numeric_primary %= numeric_value_function | value_expression_primary;
  numeric_primary.name ("numeric_primary");

  factor %= -sign >> numeric_primary;
  factor.name ("factor");

  result_expression_string %= value_expression_string;
  result_string %= result_expression_string
                   | ascii::no_case[ascii::string ("NULL")];

  general_set_function_string
      %= (hold[lexeme[set_function_type >> &nonidentifier_character]]
          > char_ ('(')) >> -set_quantifier > value_expression_string
         > char_ (')');
  set_function_specification_string
      %= (hold[ascii::no_case[ascii::string ("COUNT")] >> char_ ('(')
               >> char_ ('*')] > char_ (')')) | general_set_function_string;

  when_operand %= value_expression_string;
  
  simple_when_clause_string
      %= ascii::no_case[ascii::string ("WHEN")]
         >> no_skip[boost::spirit::qi::space] >> when_operand
         > ascii::no_case[ascii::string ("THEN")]
         > no_skip[boost::spirit::qi::space] > result_string;

  else_clause_string %= ascii::no_case[ascii::string ("ELSE")]
                        >> no_skip[boost::spirit::qi::space] >> result_string;

  case_operand %= value_expression_string;
  simple_case_string
      %= ascii::no_case[ascii::string ("CASE")]
         >> no_skip[boost::spirit::qi::space] >> case_operand
         > +hold[no_skip[boost::spirit::qi::space]
                 >> simple_when_clause_string]
         >> -hold[no_skip[boost::spirit::qi::space] >> else_clause_string]
         > no_skip[boost::spirit::qi::space]
         > ascii::no_case[ascii::string ("END")];
  case_specification_string %= simple_case_string;
  case_expression_string %= case_specification_string;

  any_expression_string %= ascii::no_case[ascii::string ("ANY")] >> char_ ('(')
                           > value_expression_string > char_ (')');

  trig_function_string
      %= (hold[lexeme[(ascii::no_case[ascii::string ("ACOS")]
                       | ascii::no_case[ascii::string ("ASIN")]
                       | ascii::no_case[ascii::string ("ATAN")]
                       | ascii::no_case[ascii::string ("COS")]
                       | ascii::no_case[ascii::string ("COT")]
                       | ascii::no_case[ascii::string ("SIN")]
                       | ascii::no_case[ascii::string ("TAN")])
                      >> &nonidentifier_character]] > char_ ('(')
          > numeric_value_expression_string > char_ (')'))
         | (hold[lexeme[ascii::no_case[ascii::string ("ATAN2")]
                        >> &nonidentifier_character]] > char_ ('(')
            > numeric_value_expression_string > char_ (',')
            > numeric_value_expression_string > char_ (')'));

  math_function_string
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
          > numeric_value_expression_string > char_ (')'))
         | (hold[lexeme[(ascii::no_case[ascii::string ("MOD")]
                         | ascii::no_case[ascii::string ("POWER")])
                        >> &nonidentifier_character]] > char_ ('(')
            > numeric_value_expression_string > char_ (',')
            > numeric_value_expression_string > char_ (')'))
         | (hold[lexeme[ascii::no_case[ascii::string ("PI")]
                        >> &nonidentifier_character]] > char_ ('(')
            > char_ (')'))
         | (hold[lexeme[ascii::no_case[ascii::string ("RAND")]
                        >> &nonidentifier_character]] > char_ ('(')
            >> -numeric_value_expression_string > char_ (')'))
         | (hold[lexeme[(ascii::no_case[ascii::string ("ROUND")]
                         | ascii::no_case[ascii::string ("TRUNCATE")])
                        >> &nonidentifier_character]] > char_ ('(')
            > numeric_value_expression_string
            >> -(char_ (',') > signed_integer) > char_ (')'));

  value_expression_primary_string
      %= (array_value_constructor_by_enumeration_string
          | unsigned_value_specification | column_reference_string
          | set_function_specification_string | case_expression_string
          | any_expression_string
          | hold[char_ ('(') >> value_expression_string >> char_ (')')])
         >> *(char_ ('[') >> numeric_value_expression_string >> char_ (']'));

  user_defined_function_param_string %= value_expression_string;
  user_defined_function_string
      %= hold[user_defined_function_name >> char_ ('(')]
         /// Use this awkward syntax instead of the usual list parser so
         /// that the attribute is still a string overall.
         >> -(user_defined_function_param_string
              >> *(char_ (',') >> user_defined_function_param_string))
         >> char_ (')');

  cast_function_string
      %= hold[ascii::no_case[ascii::string ("CAST")] >> char_ ('(')
              >> value_expression_string >> no_skip[boost::spirit::qi::space]
              >> ascii::no_case[ascii::string ("AS")]
              >> no_skip[boost::spirit::qi::space]
              > (ascii::no_case[ascii::string ("NUMERIC")]
                 | ascii::no_case[ascii::string ("FLOAT4")]
                 | ascii::no_case[ascii::string ("FLOAT8")]) > char_ (')')];
  numeric_value_function_string %= trig_function_string | math_function_string
                                   | cast_function_string
                                   | user_defined_function_string;
  numeric_primary_string %= numeric_value_function_string
                            | value_expression_primary_string;
  factor_string %= -sign >> numeric_primary_string;
}
