#include "../../ADQL_parser.hxx"

void ADQL_parser::init_strings ()
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

  column_reference_string
      %= hold[tap_upload >> period >> identifier]
         | hold[catalog_name >> period >> unqualified_schema_name >> period
                >> identifier >> period >> identifier]
         | hold[unqualified_schema_name >> period >> identifier >> period
                >> identifier] | hold[identifier >> period >> identifier]
         | identifier;

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

  term_string %= factor_string >> -(char_ ("*/") >> term_string);
  numeric_value_expression_string
      %= term_string >> -(char_ ("+-") >> numeric_value_expression_string);

  concatenation_operator_string %= ascii::string ("||");
  /// Flip the order of character_factor and
  /// character_value_expression to prevent recursion.
  character_value_expression_string
      %= character_factor_string >> -(concatenation_operator_string
                                      >> character_value_expression_string);
  character_primary_string %= string_value_function
                              | value_expression_primary_string;
  character_factor_string %= character_primary_string;
  string_value_expression_string %= character_value_expression_string;

  /// Custom array_expression so that SQL 99 array literals can pass
  /// through.

  /// This has to be in a different translation unit than
  /// value_expression_string.  Otherwise Spirit will recurse
  /// infinitely trying to optimize it.
  array_value_constructor_by_enumeration_string
      %= hold[ascii::no_case[ascii::string ("ARRAY")] >> char_ ('[')
              >> -(value_expression_string
                   >> *(char_ (',') >> value_expression_string))
              > char_ (']')];
  value_expression_string
      %= (hold[character_factor_string >> concatenation_operator_string]
          >> character_value_expression_string)
         | numeric_value_expression_string | string_value_expression_string;
}
