#include "../../ADQL_parser.hxx"

void ADQL_parser::init_math ()
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

  /// Include names that optionally have zero arg.
  math_zero_arg_names %= ascii::no_case[ascii::string ("PI")]
                         | ascii::no_case[ascii::string ("RAND")];

  math_zero_arg %= math_zero_arg_names >> '(' >> ')';

  /// Include names that optionally have one arg.
  math_one_arg_names %= ascii::no_case[ascii::string ("ABS")]
                        | ascii::no_case[ascii::string ("CEILING")]
                        | ascii::no_case[ascii::string ("DEGREES")]
                        | ascii::no_case[ascii::string ("EXP")]
                        | ascii::no_case[ascii::string ("FLOOR")]
                        | ascii::no_case[ascii::string ("LOG10")]
                        | ascii::no_case[ascii::string ("LOG")]
                        | ascii::no_case[ascii::string ("RADIANS")]
                        | ascii::no_case[ascii::string ("SQRT")]
                        | ascii::no_case[ascii::string ("RAND")]
                        | ascii::no_case[ascii::string ("ROUND")]
                        | ascii::no_case[ascii::string ("TRUNCATE")];

  math_one_arg %= math_one_arg_names >> '(' >> value_expression >> ')';

  /// Include names that optionally have two args.
  math_two_arg_names %= ascii::no_case[ascii::string ("MOD")]
                        | ascii::no_case[ascii::string ("POWER")]
                        | ascii::no_case[ascii::string ("ROUND")]
                        | ascii::no_case[ascii::string ("TRUNCATE")];

  math_two_arg %= math_two_arg_names >> '(' >> value_expression >> ','
                  >> value_expression >> ')';

  math_function %= math_zero_arg | math_one_arg | math_two_arg;
  math_function.name ("math_function");
}
