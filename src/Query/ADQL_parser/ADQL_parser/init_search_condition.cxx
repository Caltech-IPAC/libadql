#include "../../ADQL_parser.hxx"

void ADQL_parser::init_search_condition ()
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

  boolean_literal %= ascii::no_case[ascii::string ("True")]
                     | ascii::no_case[ascii::string ("False")];

  boolean_value_expression %= boolean_literal | user_defined_function_string;

  boolean_primary %= predicate
                     | hold[lit ('(') >> search_condition >> lit (')')]
                     | boolean_value_expression;

  boolean_factor %= -lexeme[ascii::no_case[ascii::string ("NOT")]
                            >> &boost::spirit::qi::space] >> boolean_primary;

  boolean_term %= boolean_factor
                  >> lexeme[(ascii::no_case[ascii::string ("AND")]
                             | ascii::no_case[ascii::string ("OR")])
                            >> &boost::spirit::qi::space] >> search_condition;

  search_condition
      = (boolean_term | boolean_factor)[push_back (at_c<0>(_val), _1)];
}
