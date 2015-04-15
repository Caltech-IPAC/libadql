#include "../../ADQL_parser.hxx"

ADQL_parser::ADQL_parser (const std::map<std::string, std::string> &Table_mapping)
  : ADQL_parser::base_type (query, "ADQL query"),
    table_mapping (Table_mapping)
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

  init_reserved_words ();
  init_identifier ();
  init_geometry ();
  init_column_reference ();
  init_literals ();
  init_factor ();
  init_columns ();
  init_factor ();
  init_join ();
  init_predicate ();
  init_search_condition ();
  init_query ();
}
