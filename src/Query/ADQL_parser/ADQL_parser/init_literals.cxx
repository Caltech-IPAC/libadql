#include "../../ADQL_parser.hxx"

void ADQL_parser::init_literals()
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

  unsigned_integer %= +digit;
  exact_numeric_literal
    %= (unsigned_integer >> -(period >> unsigned_integer))
    | (period >> unsigned_integer);

  sign %= char_ ('+') | char_ ('-');
  signed_integer %= -sign >> unsigned_integer;
  signed_integer.name ("signed_integer");
  mantissa %= exact_numeric_literal;
  exponent %= signed_integer;
  approximate_numeric_literal %= mantissa >> char_ ("Ee") >> exponent;
  unsigned_numeric_literal %= exact_numeric_literal
    | approximate_numeric_literal;

  quote %= char_ ('\'');
  space %= char_ (' ');
  newline %= char_ ('\n');
  tab %= char_ ('\t');
  minus_sign %= char_ ('-');

  nonquote_character %= char_ - quote;
  character_representation %= nonquote_character | ascii::string ("''");

  comment_introducer %= minus_sign >> +minus_sign;
  comment_character %= char_ - newline;
  comment %= comment_introducer >> *comment_character >> newline;

  separator %= comment | space | newline;

  character_string_literal
    %= quote >> *character_representation >> quote
             >> *hold[+separator >> quote >> *character_representation >> quote];

  general_literal %= character_string_literal;
  unsigned_literal %= unsigned_numeric_literal | general_literal;
  unsigned_value_specification %= unsigned_literal;
}
