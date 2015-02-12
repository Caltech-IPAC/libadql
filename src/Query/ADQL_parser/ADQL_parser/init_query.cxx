#include "../../ADQL_parser.hxx"

void ADQL_parser::init_query ()
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

  where = lexeme[ascii::no_case["WHERE"] > &boost::spirit::qi::space]
          >> ((geometry[at_c<0>(_val) = _1]
               >> -(ascii::no_case["AND"] >> '('
                    >> search_condition[at_c<1>(_val) = _1] >> ')'))
              | (lit ('(') >> search_condition[at_c<1>(_val) = _1] >> ')'
                 >> (lexeme[ascii::no_case["AND"] > &boost::spirit::qi::space]
                     >> geometry[at_c<0>(_val) = _1]))
              | (search_condition[at_c<1>(_val) = _1]));
  where.name ("where");

  grouping_column_reference %= column_reference;
  grouping_column_reference_list %= grouping_column_reference
                                    >> *(char_ (',') >> column_reference);
  group_by_clause
      %= lexeme[ascii::no_case["GROUP"] > &boost::spirit::qi::space]
         > lexeme[ascii::no_case["BY"] > &boost::spirit::qi::space]
         > grouping_column_reference_list;
  group_by_clause.name ("group by");

  having_clause %= lexeme[ascii::no_case["HAVING"] > &boost::spirit::qi::space]
                   > search_condition;
  having_clause.name ("having");

  sort_key %= column_name | unsigned_integer;
  ordering_specification %= ascii::no_case[ascii::string ("ASC")]
                            | ascii::no_case[ascii::string ("DESC")];
  /// I have the vague feeling that there are cases where there are
  /// no spaces between the sort_key and ordering_specification, but
  /// I can not think of any.
  sort_specification
      %= sort_key >> -(boost::spirit::qi::space >> ordering_specification);
  sort_specification_list %= sort_specification
                             >> *(char_ (',') >> sort_specification);
  order_by_clause
      %= lexeme[ascii::no_case["ORDER"] > &boost::spirit::qi::space]
         >> lexeme[ascii::no_case["BY"] > &boost::spirit::qi::space]
         >> sort_specification_list;
  order_by_clause.name ("order by");

  query %= lexeme[ascii::no_case["SELECT"] > &boost::spirit::qi::space]
           >> -set_quantifier
           >> -(hold[lexeme[ascii::no_case["TOP"] >> &boost::spirit::qi::space]]
               > lexeme[ulong_long > &boost::spirit::qi::space]) >> columns
           >> from_clause >> -where >> -group_by_clause >> -having_clause
           >> -order_by_clause;
  query.name ("select");

  boost::spirit::qi::on_error<boost::spirit::qi::fail>(
      query, boost::phoenix::ref ((std::ostream &)error_stream)
             << boost::phoenix::val ("Error: Expecting ")
             << boost::spirit::qi::labels::_4
             << boost::phoenix::val (" here: \"")
             << boost::phoenix::construct<std::string>(_3, _2)
             << boost::phoenix::val ("\"") << std::endl);
}
