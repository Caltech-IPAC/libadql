#include "../../ADQL_parser.hxx"

void ADQL_parser::init_predicate ()
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

  derived_correlation %= subquery >> correlation_specification;

  table_reference %= joined_table | table_correlation | derived_correlation;
  table_reference.name ("table reference");

  from_clause %= lexeme[ascii::no_case["FROM"] > &boost::spirit::qi::space]
                 > (table_reference % ",");
  from_clause.name ("from");

  comparison_predicate
      %= value_expression_string
         >> (ascii::string ("=") | ascii::string ("!=") | ascii::string ("<>")
             | ascii::string ("<=") | ascii::string (">=")
             | ascii::string ("<") | ascii::string (">")) >> value_expression_string;

  between_predicate
      %= value_expression_string >> -lexeme[ascii::no_case[ascii::string ("NOT")]
                                     > &boost::spirit::qi::space]
         >> lexeme[ascii::no_case["BETWEEN"] > &boost::spirit::qi::space]
         >> value_expression_string
         >> lexeme[ascii::no_case["AND"] > &boost::spirit::qi::space]
         >> value_expression_string;

  in_predicate
      %= value_expression_string >> -lexeme[ascii::no_case[ascii::string ("NOT")]
                                     > boost::spirit::qi::space]
         >> lexeme[ascii::no_case["IN"] > &boost::spirit::qi::space]
         >> (subquery | (lit ('(') >> (value_expression_string % ',') >> ')'));

  null_predicate %= value_expression_string
                    >> lexeme[ascii::no_case["IS"] > &boost::spirit::qi::space]
                    >> -lexeme[ascii::no_case[ascii::string ("NOT")]
                               > &boost::spirit::qi::space]
                    >> ascii::no_case["NULL"];

  match_value %= character_value_expression;
  pattern %= character_value_expression;

  like_predicate
      %= match_value >> -lexeme[ascii::no_case[ascii::string ("NOT")]
                                > &boost::spirit::qi::space]
         >> lexeme[ascii::no_case["LIKE"] > &boost::spirit::qi::space]
         >> pattern;

  exists_predicate
      %= lexeme[ascii::no_case["EXISTS"] > &boost::spirit::qi::space]
         >> subquery;

  predicate %= comparison_predicate | between_predicate | in_predicate
               | null_predicate | like_predicate | exists_predicate;
}
