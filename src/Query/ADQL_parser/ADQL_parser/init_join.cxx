#include "../../ADQL_parser.hxx"

void ADQL_parser::init_join ()
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

  join_type %= lexeme[ascii::no_case[ascii::string ("INNER")] >> &boost::spirit::qi::space]
    | (outer_join_type >> -lexeme[ascii::no_case[ascii::string ("OUTER")] >> &boost::spirit::qi::space]);
  join_type.name ("join type");
  
  outer_join_type %= lexeme[(ascii::no_case[ascii::string ("LEFT")]
                            | ascii::no_case[ascii::string ("RIGHT")]
                            | ascii::no_case[ascii::string ("FULL")])
                           >> &boost::spirit::qi::space];
  outer_join_type.name ("outer join type");

  join_specification %= join_condition | named_columns_join;
  join_specification.name ("join specification");

  join_condition %= lexeme[ascii::no_case["ON"] >> &boost::spirit::qi::space]
    >> search_condition;
  join_condition.name ("join condition");

  named_columns_join %= lexeme[ascii::no_case["USING"] >> &boost::spirit::qi::space]
    >> lit ('(') >> join_column_list >> lit (')');
  named_columns_join.name ("named columns join");

  join_column_list %= column_name_list;
  column_name_list.name ("join column list");

  column_name_list %= column_name % ',';
  column_name_list.name ("column name list");
}
