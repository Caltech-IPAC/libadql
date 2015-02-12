#include "../../ADQL_parser.hxx"

void ADQL_parser::init_identifier()
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

  keyword %= (SQL_reserved_word | ADQL_reserved_word)
    >> &!(digit | simple_Latin_letter | char_ ("_"));

  simple_Latin_letter %= char_ ("a-zA-Z");
  identifier_character %= digit | simple_Latin_letter | char_ ("_");
  /// nonidentifier_character is to signal that, for example, in an
  /// AND, clause, AND is followed by something that is not an
  /// identifier (e.g. a space or parentheses).
  nonidentifier_character %= char_ - identifier_character;
  nonidentifier_character.name ("nonidentifier character");
  all_identifiers %= simple_Latin_letter >> *(identifier_character);
  regular_identifier %= all_identifiers - keyword;

  SQL_special_character
    %= char_ (' ') | char_ ('"') | char_ ('%') | char_ ('&') | char_ ('\'')
    | char_ ('(') | char_ (')') | char_ ('*') | char_ ('+')
    | char_ (',') | char_ ('-') | char_ ('.') | char_ ('/')
    | char_ (':') | char_ (';') | char_ ('<') | char_ ('>')
    | char_ ('=') | char_ ('?') | char_ ('_') | char_ ('|');
  SQL_language_character %= alnum | SQL_special_character;
  nondoublequote_character %= SQL_language_character - char_ ('"');
  /// Note that all of these delimited_identifier* rules do not skip spaces
  delimited_identifier_part %= nondoublequote_character
    | ascii::string ("\"\"");
  delimited_identifier_body %= +delimited_identifier_part;
  delimited_identifier %= char_ ('"') >> delimited_identifier_body
                                      >> char_ ('"');

  identifier %= regular_identifier | delimited_identifier;
  identifier.name ("identifier");
}
