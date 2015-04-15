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

  table_correlation %= table_name >> -correlation_specification;

  outer_join = lexeme[(ascii::no_case[ascii::string ("LEFT")]
                       | ascii::no_case[ascii::string ("RIGHT")]
                       | ascii::no_case[ascii::string ("FULL")])
                      >> &boost::spirit::qi::space][at_c<0>(_val)=_1]
    >> -lexeme[ascii::no_case[ascii::string ("OUTER")]
               >> &boost::spirit::qi::space][at_c<1>(_val)=true];
  outer_join.name ("outer join type");

  join_type %= lexeme[ascii::no_case[ascii::string ("INNER")]
                      >> &boost::spirit::qi::space] | outer_join;
  join_type.name ("join type");
  
  join_suffix = -(lexeme[ascii::no_case["NATURAL"] >> &boost::spirit::qi::space]
                  [at_c<0>(_val)=true])
    >> -join_type[at_c<1>(_val)=_1]
    >> lexeme[ascii::no_case["JOIN"] >> &boost::spirit::qi::space]
    > (table_reference[at_c<2>(_val)=_1]
       >> -join_specification[at_c<3>(_val)=_1]);

  qualified_join %= table_correlation >> join_suffix;
  qualified_join.name ("qualified join");

  joined_table %= (qualified_join | (lit('(') >> joined_table >> lit(')')))
    >> -join_suffix;
  joined_table.name ("joined table");

  /// We can not just use the option operator '-' on correlation_join
  /// because it has a table_reference embedded within it.  We need a
  /// separate rule, table_correlation, in Table_Reference::Variant
  /// that does not have table_reference embedded.
  correlation_join %= table_correlation >> join_suffix;
  correlation_join.name ("correlation_join");

  table_reference %= correlation_join | table_correlation | joined_table;
  // table_reference %= joined_table | table_correlation;
  // FIXME: table_reference is supposed to include derived_table
  // | (derived_table >> correlation_specification)
  table_reference.name ("table reference");

  from_clause %= lexeme[ascii::no_case["FROM"] > &boost::spirit::qi::space]
    > (table_reference % ",");
  from_clause.name ("from");

  comparison_predicate %= value_expression
    >> (ascii::string ("=") | ascii::string ("!=")
        | ascii::string ("<>") | ascii::string ("<=")
        | ascii::string (">=") | ascii::string ("<")
        | ascii::string (">")) >> value_expression;

  between_predicate
    %= value_expression
    >> -lexeme[ascii::no_case[ascii::string ("NOT")]
               > &boost::spirit::qi::space]
    >> lexeme[ascii::no_case["BETWEEN"]
              > &boost::spirit::qi::space]
    >> value_expression
    >> lexeme[ascii::no_case["AND"] > &boost::spirit::qi::space]
    >> value_expression;

  in_predicate
    %= value_expression
    >> -lexeme[ascii::no_case[ascii::string ("NOT")]
               > boost::spirit::qi::space]
    >> lexeme[ascii::no_case["IN"]
              > &boost::spirit::qi::space]
    // FIXME: This should be table_subquery, not value_expression
    >> (value_expression
        | (lit ('(') >> (value_expression % ',') >> ')'));

  null_predicate
    %= value_expression
    >> lexeme[ascii::no_case["IS"] > &boost::spirit::qi::space]
    >> -lexeme[ascii::no_case[ascii::string ("NOT")]
               > &boost::spirit::qi::space] >> ascii::no_case["NULL"];

  match_value %= character_value_expression;
  pattern %= character_value_expression;

  like_predicate
    %= match_value >> -lexeme[ascii::no_case[ascii::string ("NOT")]
                              > &boost::spirit::qi::space]
                   >> lexeme[ascii::no_case["LIKE"] > &boost::spirit::qi::space]
                   >> pattern;

  // FIXME: add exists
  predicate %= (comparison_predicate | between_predicate | in_predicate
                | null_predicate | like_predicate);
}
