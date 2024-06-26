#pragma once
#include <sstream>

#if 0
#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_OUT std::cout

#define DEBUG_COL
#define DEBUG_FAC
#define DEBUG_LIT
#define DEBUG_MATH
#define DEBUG_PRED
#define DEBUG_Q
#define DEBUG_TRIG
#define DEBUG_VAL
#define DEBUG_WHERE
#endif

#define BOOST_SPIRIT_THREADSAFE

#include <boost/bind.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include "boost/variant.hpp"

#include "../Query.hxx"

// This parser does not have a separate lexer.  That makes things a
// little more complicated because I have to be sure to check for
// things like LOG10 before LOG or my_identifier() before
// my_identifier.  I think it all works, but I have a feeling that
// there are some corner cases errors because of that.

struct ADQL_parser : boost::spirit::qi::grammar<std::string::const_iterator,
                                                ADQL::Query_Specification(),
                                                boost::spirit::qi::locals<std::string>,
                                                boost::spirit::ascii::space_type> {
    ADQL_parser(const std::map<std::string, std::string> &Table_mapping);

    void init_reserved_words();
    void init_identifier();
    void init_join();
    void init_column_reference();
    void init_point_or_column();
    void init_geometry();
    void init_non_predicate_geometry_function();
    void init_correlation_specification();
    void init_literals();
    void init_math();
    void init_trig();
    void init_factor();
    void init_columns();
    void init_value_expression();
    void init_predicate();
    void init_search_condition();
    void init_query();

    std::stringstream error_stream;

    std::map<std::string, std::string> table_mapping;

    // symbols for enum classes
    boost::spirit::qi::symbols<char, ADQL::Coord_Sys::Reference_Frame> reference_frames;
    boost::spirit::qi::symbols<char, ADQL::Coord_Sys::Reference_Position>
            reference_positions;

    // no-skipper rules for char
    boost::spirit::qi::rule<std::string::const_iterator, char()> simple_Latin_letter,
            identifier_character, nonidentifier_character, nondoublequote_character,
            possibly_qualified_identifier_character, quote, space, newline, tab,
            minus_sign, nonquote_character, sign, period, arithmetic_operator,
            char_flag;

    // no-skipper rules for std::string
    boost::spirit::qi::rule<std::string::const_iterator, std::string()>
            unsigned_integer, exact_numeric_literal, signed_integer, mantissa, exponent,
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
            column_name, ordering_specification, set_function_type, table_name,
            tap_upload, tap_upload_identifier, unqualified_schema_name, catalog_name,
            correlation_name, qualifier, trig_one_arg_names, math_zero_arg_names,
            math_one_arg_names, math_two_arg_names, cast_as, user_defined_function_name,
            unsigned_literal, unsigned_value_specification, general_literal,
            null_literal, null_cast, boolean_literal, qualifier_star, binary_operators,
            geo_one_arg_names, geo_two_arg_names, with_table_name, with_column_name,
            possibly_qualified_identifier, table_valued_function_name,
            table_valued_function_param, sql_no_arg_function;

    // rules with skipper
    boost::spirit::qi::rule<std::string::const_iterator, std::string(),
                            boost::spirit::ascii::space_type>
            correlation_specification, count_star;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Coord_Sys(),
                            boost::spirit::ascii::space_type>
            coord_sys;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Coordinate(),
                            boost::spirit::ascii::space_type>
            coord;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Binary_Arithmetic_Expression(),
                            boost::spirit::ascii::space_type>
            binary_arithmetic_expression;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Column_or_Simple_Arithmetic_Expression(),
                            boost::spirit::ascii::space_type>
            column_or_simple_arithmetic_expression;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Catalog_Schema_Qualifier_Column(),
                            boost::spirit::ascii::space_type>
            catalog_schema_qualifier_column;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Schema_Qualifier_Column(),
                            boost::spirit::ascii::space_type>
            schema_qualifier_column;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Qualifier_Column(),
                            boost::spirit::ascii::space_type>
            qualifier_column;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Column_Reference(),
                            boost::spirit::ascii::space_type>
            column_reference;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Select::Column_Variant(),
                            boost::spirit::ascii::space_type>
            select_item;

    boost::spirit::qi::rule<std::string::const_iterator,
                            std::vector<ADQL::Select::Column_Variant>(),
                            boost::spirit::ascii::space_type>
            select_list;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Select::Columns(),
                            boost::spirit::ascii::space_type>
            columns;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Select(),
                            boost::spirit::ascii::space_type>
            select;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Select_From_Where(),
                            boost::spirit::ascii::space_type>
            select_from_where, select_from_where_initial, select_from_where_no_geometry,
            select_from_where_initial_no_geometry;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::SFW_Addon(),
                            boost::spirit::ascii::space_type>
            select_from_where_addon, select_from_where_addon_no_geometry;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Select_From_Where_List::SFW_Addon_List(),
                            boost::spirit::ascii::space_type>
            select_from_where_addon_list, select_from_where_addon_no_geometry_list;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Select_From_Where_List(),
                            boost::spirit::ascii::space_type>
            select_from_where_list, select_from_where_no_geometry_list;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::As(),
                            boost::spirit::ascii::space_type>
            as;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Non_As(),
                            boost::spirit::ascii::space_type>
            non_as;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Factor(),
                            boost::spirit::ascii::space_type>
            factor;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Numeric_Primary(),
                            boost::spirit::ascii::space_type>
            numeric_primary;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Numeric_Value_Function(),
                            boost::spirit::ascii::space_type>
            numeric_value_function;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Trig_Function(),
                            boost::spirit::ascii::space_type>
            trig_function;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Trig_One_Arg(),
                            boost::spirit::ascii::space_type>
            trig_one_arg;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Trig_Two_Arg(),
                            boost::spirit::ascii::space_type>
            trig_two_arg;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Math_Function(),
                            boost::spirit::ascii::space_type>
            math_function;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Math_Zero_Arg(),
                            boost::spirit::ascii::space_type>
            math_zero_arg;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Math_One_Arg(),
                            boost::spirit::ascii::space_type>
            math_one_arg;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Math_Two_Arg(),
                            boost::spirit::ascii::space_type>
            math_two_arg;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Cast_Function(),
                            boost::spirit::ascii::space_type>
            cast_function;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::User_Defined_Function(),
                            boost::spirit::ascii::space_type>
            user_defined_function;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Value_Expression(),
                            boost::spirit::ascii::space_type>
            value_expression, user_defined_function_param, pattern;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Value_Expression_Non_Bool_Term(),
                            boost::spirit::ascii::space_type>
            value_expression_non_bool_term;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Value_Expression_Non_Bool(),
                            boost::spirit::ascii::space_type>
            value_expression_non_bool, match_value;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Value_Expression_Primary(),
                            boost::spirit::ascii::space_type>
            value_expression_primary;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Array_Constructor(),
                            boost::spirit::ascii::space_type>
            array_constructor;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Array_Index(),
                            boost::spirit::ascii::space_type>
            array_index;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Set_Function_Specification(),
                            boost::spirit::ascii::space_type>
            set_function_specification;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::General_Set_Function(),
                            boost::spirit::ascii::space_type>
            general_set_function;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::General_Set_Args(),
                            boost::spirit::ascii::space_type>
            general_set_args;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Case_Expression(),
                            boost::spirit::ascii::space_type>
            case_expression;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Case_Abbreviation(),
                            boost::spirit::ascii::space_type>
            case_abbreviation;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Nullif(),
                            boost::spirit::ascii::space_type>
            nullif;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Coalesce(),
                            boost::spirit::ascii::space_type>
            coalesce;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Case_Specification(),
                            boost::spirit::ascii::space_type>
            case_specification;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Simple_Case(),
                            boost::spirit::ascii::space_type>
            simple_case;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Simple_Whens(),
                            boost::spirit::ascii::space_type>
            simple_whens;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Simple_When(),
                            boost::spirit::ascii::space_type>
            simple_when;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Searched_Case(),
                            boost::spirit::ascii::space_type>
            searched_case;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Searched_Whens(),
                            boost::spirit::ascii::space_type>
            searched_whens;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Searched_When(),
                            boost::spirit::ascii::space_type>
            searched_when;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Result(),
                            boost::spirit::ascii::space_type>
            result;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Else_Clause(),
                            boost::spirit::ascii::space_type>
            else_clause;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Any_Expression(),
                            boost::spirit::ascii::space_type>
            any_expression;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Value_Subexpression(),
                            boost::spirit::ascii::space_type>
            value_subexpression;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Table_Correlation(),
                            boost::spirit::ascii::space_type>
            table_correlation;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Table_Reference(),
                            boost::spirit::ascii::space_type>
            table_reference;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Table_Valued_Function(),
                            boost::spirit::ascii::space_type>
            table_valued_function;

    boost::spirit::qi::rule<std::string::const_iterator,
                            std::vector<ADQL::Table_Reference>(),
                            boost::spirit::ascii::space_type>
            from_clause;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Point(),
                            boost::spirit::ascii::space_type>
            point;
    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Point_or_Column(),
                            boost::spirit::ascii::space_type>
            point_or_column;
    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Circle(),
                            boost::spirit::ascii::space_type>
            circle;
    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Ellipse(),
                            boost::spirit::ascii::space_type>
            ellipse;
    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Box(),
                            boost::spirit::ascii::space_type>
            box;
    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Polygon(),
                            boost::spirit::ascii::space_type>
            polygon;
    boost::spirit::qi::rule<std::string::const_iterator,
                            std::vector<ADQL::Coordinate>(),
                            boost::spirit::ascii::space_type>
            coord_list;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Contains(),
                            boost::spirit::ascii::space_type>
            contains;
    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Intersects(),
                            boost::spirit::ascii::space_type>
            intersects;
    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Shape(),
                            boost::spirit::ascii::space_type>
            shape;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Shape_or_Column(),
                            boost::spirit::ascii::space_type>
            shape_or_column;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Non_Predicate_Geometry_Function(),
                            boost::spirit::ascii::space_type>
            non_predicate_geometry_function;
    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Non_Predicate_Geometry_Function_One_Arg(),
                            boost::spirit::ascii::space_type>
            non_predicate_geometry_function_one_arg;
    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Non_Predicate_Geometry_Function_Two_Arg(),
                            boost::spirit::ascii::space_type>
            non_predicate_geometry_function_two_arg;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Geometry::Geometry_Left(),
                            boost::spirit::ascii::space_type>
            geometry_left;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Geometry::Geometry_Right(),
                            boost::spirit::ascii::space_type>
            geometry_right;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Geometry(),
                            boost::spirit::ascii::space_type>
            geometry;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Comparison_Predicate(),
                            boost::spirit::ascii::space_type>
            comparison_predicate;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Between_Predicate(),
                            boost::spirit::ascii::space_type>
            between_predicate;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::In_Predicate(),
                            boost::spirit::ascii::space_type>
            in_predicate;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Null_Predicate(),
                            boost::spirit::ascii::space_type>
            null_predicate;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Like_Predicate(),
                            boost::spirit::ascii::space_type>
            like_predicate;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Exists_Predicate(),
                            boost::spirit::ascii::space_type>
            exists_predicate;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Predicate(),
                            boost::spirit::ascii::space_type>
            predicate;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Boolean_Primary(),
                            boost::spirit::ascii::space_type>
            boolean_primary;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Boolean_Factor(),
                            boost::spirit::ascii::space_type>
            boolean_factor;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Boolean_Term(),
                            boost::spirit::ascii::space_type>
            boolean_term;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Search_Condition(),
                            boost::spirit::ascii::space_type>
            search_condition, boolean_value_expression;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Having(),
                            boost::spirit::ascii::space_type>
            having;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Group_By_Term(),
                            boost::spirit::ascii::space_type>
            group_by_term;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Group_By(),
                            boost::spirit::ascii::space_type>
            group_by;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Order_By(),
                            boost::spirit::ascii::space_type>
            order_by;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Sort_Specification(),
                            boost::spirit::ascii::space_type>
            sort_specification;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Sort_Key(),
                            boost::spirit::ascii::space_type>
            sort_key;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::With(),
                            boost::spirit::ascii::space_type>
            with;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Where(),
                            boost::spirit::ascii::space_type>
            where, where_no_geometry;

    boost::spirit::qi::rule<std::string::const_iterator, std::vector<std::string>(),
                            boost::spirit::ascii::space_type>
            join_column_list, column_name_list;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Named_Columns_Join(),
                            boost::spirit::ascii::space_type>
            named_columns_join;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Join_Suffix::Join_Type(),
                            boost::spirit::ascii::space_type>
            join_type;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Outer_Join(),
                            boost::spirit::ascii::space_type>
            outer_join;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Join_Condition(),
                            boost::spirit::ascii::space_type>
            join_condition;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Join_Specification(),
                            boost::spirit::ascii::space_type>
            join_specification;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Join_Suffix(),
                            boost::spirit::ascii::space_type>
            join_suffix;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Correlation_Join(),
                            boost::spirit::ascii::space_type>
            correlation_join;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Qualified_Join(),
                            boost::spirit::ascii::space_type>
            qualified_join, join_parentheses;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Joined_Table(),
                            boost::spirit::ascii::space_type>
            joined_table;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Derived_Correlation(),
                            boost::spirit::ascii::space_type>
            derived_correlation;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Subquery(),
                            boost::spirit::ascii::space_type>
            subquery;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Query_Specification(),
                            boost::spirit::ascii::space_type>
            query_no_geometry;

    boost::spirit::qi::rule<std::string::const_iterator, ADQL::Query_Specification(),
                            boost::spirit::qi::locals<std::string>,
                            boost::spirit::ascii::space_type>
            query;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Coord_Sys::Reference_Frame(),
                            boost::spirit::ascii::space_type>
            reference_frame;

    boost::spirit::qi::rule<std::string::const_iterator,
                            ADQL::Coord_Sys::Reference_Position(),
                            boost::spirit::ascii::space_type>
            reference_position;
};
