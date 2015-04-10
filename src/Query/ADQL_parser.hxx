#pragma once

#include <sstream>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"
#include <boost/bind.hpp>

#include "../Query.hxx"

/// This parser does not have a separate lexer.  That makes things a
/// little more complicated because I have to be sure to check for
/// things like LOG10 before LOG or my_identifier() before
/// my_identifier.  I think it all works, but I have a feeling that
/// there are some corner cases errors because of that.

struct ADQL_parser
    : boost::spirit::qi::grammar<std::string::const_iterator, ADQL::Query (),
                                 boost::spirit::qi::locals<std::string>,
                                 boost::spirit::ascii::space_type>
{

  ADQL_parser (const std::map<std::string, std::string> &Table_mapping);

  void init_reserved_words ();
  void init_identifier ();
  void init_join ();
  void init_geometry ();
  void init_column_reference ();
  void init_literals ();
  void init_factor ();
  void init_columns ();
  void init_predicate ();
  void init_search_condition ();
  void init_query ();

  std::stringstream error_stream;

  std::map<std::string, std::string> table_mapping;

  boost::spirit::qi::rule<std::string::const_iterator, char()> simple_Latin_letter,
      identifier_character, nonidentifier_character, SQL_language_character,
      SQL_special_character, nondoublequote_character, quote, space, newline,
      tab, minus_sign, nonquote_character, sign, period;

  boost::spirit::qi::rule<std::string::const_iterator, std::string ()> unsigned_integer,
      exact_numeric_literal, signed_integer, mantissa, exponent,
      approximate_numeric_literal, unsigned_numeric_literal, comment,
      comment_introducer, comment_character, delimited_identifier,
      delimited_identifier_part, delimited_identifier_body,
      character_representation, ADQL_reserved_word, SQL_reserved_word,
      SQL_reserved_word_0, SQL_reserved_word_1, SQL_reserved_word_2,
      SQL_reserved_word_3, SQL_reserved_word_00, SQL_reserved_word_01,
      SQL_reserved_word_02, SQL_reserved_word_03, SQL_reserved_word_10,
      SQL_reserved_word_11, SQL_reserved_word_12, SQL_reserved_word_13,
      SQL_reserved_word_20, SQL_reserved_word_21, SQL_reserved_word_22,
      SQL_reserved_word_23, SQL_reserved_word_30, SQL_reserved_word_31,
      SQL_reserved_word_32, keyword, all_identifiers, regular_identifier,
      identifier, set_quantifier, character_string_literal, separator,
      column_name, sort_key, ordering_specification, sort_specification,
      concatenation_operator, set_function_type,
      outer_join_type, join_type;

  boost::spirit::qi::rule<std::string::const_iterator, std::string (),
                          boost::spirit::ascii::space_type> column_reference,
      qualifier, correlation_name, table_name, tap_upload,
      unqualified_schema_name, catalog_name, general_literal, unsigned_literal,
      unsigned_value_specification, general_set_function,
      set_function_specification, value_expression_primary, value_expression,
      numeric_value_expression, numeric_primary, factor, term,
      numeric_value_function, trig_function, math_function,
      user_defined_function, user_defined_function_name,
      user_defined_function_param, default_function_prefix,
      grouping_column_reference, grouping_column_reference_list,
      group_by_clause, sort_specification_list, order_by_clause,
      string_value_function, character_primary, character_factor,
      character_value_expression, match_value, pattern,
      string_value_expression, select_non_as_item,
      correlation_specification, column_name_list, join_column_list,
      named_columns_join;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Coord_Sys (),
                          boost::spirit::ascii::space_type> coord_sys;
  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Coordinate (),
                          boost::spirit::ascii::space_type> coord;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Query::Column_Variant (),
                          boost::spirit::ascii::space_type> select_item;

  boost::spirit::qi::rule<std::string::const_iterator, std::vector<ADQL::Query::Column_Variant>(),
                          boost::spirit::ascii::space_type> select_list;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Query::Columns (),
                          boost::spirit::ascii::space_type> columns;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::As (),
                          boost::spirit::ascii::space_type> as;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Table_Reference (),
                          boost::spirit::ascii::space_type> table_reference;

  boost::spirit::qi::rule<std::string::const_iterator, std::vector<ADQL::Table_Reference>(),
                          boost::spirit::ascii::space_type> from_clause;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Point (),
                          boost::spirit::ascii::space_type> point;
  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Circle (),
                          boost::spirit::ascii::space_type> circle;
  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Ellipse (),
                          boost::spirit::ascii::space_type> ellipse;
  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Box (),
                          boost::spirit::ascii::space_type> box;
  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Polygon (),
                          boost::spirit::ascii::space_type> polygon;
  boost::spirit::qi::rule<std::string::const_iterator, std::vector<ADQL::Coordinate>(),
                          boost::spirit::ascii::space_type> coord_list;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Contains (),
                          boost::spirit::ascii::space_type> contains;
  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Contains::Shape (),
                          boost::spirit::ascii::space_type> shape;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Geometry (),
                          boost::spirit::ascii::space_type> geometry;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Comparison_Predicate (),
                          boost::spirit::ascii::space_type>
  comparison_predicate;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Between_Predicate (),
                          boost::spirit::ascii::space_type> between_predicate;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::In_Predicate (),
                          boost::spirit::ascii::space_type> in_predicate;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Null_Predicate (),
                          boost::spirit::ascii::space_type> null_predicate;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Like_Predicate (),
                          boost::spirit::ascii::space_type> like_predicate;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Predicate (),
                          boost::spirit::ascii::space_type> predicate;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Boolean_Primary (),
                          boost::spirit::ascii::space_type> boolean_primary;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Boolean_Factor (),
                          boost::spirit::ascii::space_type> boolean_factor;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Boolean_Term (),
                          boost::spirit::ascii::space_type> boolean_term;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Search_Condition (),
                          boost::spirit::ascii::space_type> search_condition;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Having (),
                          boost::spirit::ascii::space_type> having_clause;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Where (),
                          boost::spirit::ascii::space_type> where;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Join_Condition (),
                          boost::spirit::ascii::space_type> join_condition;

  boost::spirit::qi::rule<std::string::const_iterator,
                          ADQL::Join_Specification (),
                          boost::spirit::ascii::space_type> join_specification;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Qualified_Join (),
                          boost::spirit::ascii::space_type> qualified_join;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Joined_Table (),
                          boost::spirit::ascii::space_type> joined_table;

  boost::spirit::qi::rule<std::string::const_iterator, ADQL::Query (),
                          boost::spirit::qi::locals<std::string>,
                          boost::spirit::ascii::space_type> query;
};
