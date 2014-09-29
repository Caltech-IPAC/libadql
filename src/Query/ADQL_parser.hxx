#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"

#include "../Query.hxx"

/// This parser does not have a separate lexer.  That makes things a
/// little more complicated because I have to be sure to check for
/// things my LOG10 before LOG or my_identifier() before
/// my_identifier.  I think it all works, but I have a feeling that
/// there are some corner cases errors because of that.

template <typename Iterator>
struct ADQL_parser
    : boost::spirit::qi::grammar<Iterator, ADQL::Query (),
                                 boost::spirit::ascii::space_type>
{
  ADQL_parser (const std::map<std::string,std::string> &Table_mapping)
    : ADQL_parser::base_type (query), table_mapping(Table_mapping)
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

    /// Reverse sort to avoid early matches.
    ADQL_reserved_word %= ascii::no_case["TRUNCATE"]
                          | ascii::no_case["TOP"]
                          | ascii::no_case["TAN"]
                          | ascii::no_case["SQRT"]
                          | ascii::no_case["SIN"]
                          | ascii::no_case["ROUND"]
                          | ascii::no_case["REGION"]
                          | ascii::no_case["RAND"]
                          | ascii::no_case["RADIANS"]
                          | ascii::no_case["POWER"]
                          | ascii::no_case["POLYGON"]
                          | ascii::no_case["POINT"]
                          | ascii::no_case["PI"]
                          | ascii::no_case["MOD"]
                          | ascii::no_case["LOG10"]
                          | ascii::no_case["LOG"]
                          | ascii::no_case["INTERSECTS"]
                          | ascii::no_case["FLOOR"]
                          | ascii::no_case["EXP"]
                          | ascii::no_case["DISTANCE"]
                          | ascii::no_case["DEGREES"]
                          | ascii::no_case["COS"]
                          | ascii::no_case["COORDSYS"]
                          | ascii::no_case["COORD2"]
                          | ascii::no_case["COORD1"]
                          | ascii::no_case["CONTAINS"]
                          | ascii::no_case["CIRCLE"]
                          | ascii::no_case["CENTROID"]
                          | ascii::no_case["CEILING"]
                          | ascii::no_case["BOX"]
                          | ascii::no_case["ATAN2"]
                          | ascii::no_case["ATAN"]
                          | ascii::no_case["ASIN"]
                          | ascii::no_case["AREA"]
                          | ascii::no_case["ACOS"]
                          | ascii::no_case["ABS"];

    /// Split up SQL_reserved_word to help memory usage and compile times.
    SQL_reserved_word_00 %= ascii::no_case["ZONE"]
                            | ascii::no_case["YEAR"]
                            | ascii::no_case["WRITE"]
                            | ascii::no_case["WORK"]
                            | ascii::no_case["WITH"]
                            | ascii::no_case["WHERE"]
                            | ascii::no_case["WHENEVER"]
                            | ascii::no_case["WHEN"]
                            | ascii::no_case["VIEW"]
                            | ascii::no_case["VARYING"]
                            | ascii::no_case["VARCHAR"]
                            | ascii::no_case["VALUES"]
                            | ascii::no_case["VALUE"]
                            | ascii::no_case["USING"]
                            | ascii::no_case["USER"]
                            | ascii::no_case["USAGE"];

    SQL_reserved_word_01 %= ascii::no_case["UPPER"]
                            | ascii::no_case["UPDATE"]
                            | ascii::no_case["UNKNOWN"]
                            | ascii::no_case["UNIQUE"]
                            | ascii::no_case["UNION"]
                            | ascii::no_case["TRUE"]
                            | ascii::no_case["TRIM"]
                            | ascii::no_case["TRANSLATION"]
                            | ascii::no_case["TRANSLATE"]
                            | ascii::no_case["TRANSACTION"]
                            | ascii::no_case["TRAILING"]
                            | ascii::no_case["TO"]
                            | ascii::no_case["TIMEZONE_MINUTE"]
                            | ascii::no_case["TIMEZONE_HOUR"]
                            | ascii::no_case["TIMESTAMP"];

    SQL_reserved_word_02 %= ascii::no_case["TIME"]
                            | ascii::no_case["THEN"]
                            | ascii::no_case["TEMPORARY"]
                            | ascii::no_case["TABLE"]
                            | ascii::no_case["SYSTEM_USER"]
                            | ascii::no_case["SUM"]
                            | ascii::no_case["SUBSTRING"]
                            | ascii::no_case["SQLSTATE"]
                            | ascii::no_case["SQLERROR"]
                            | ascii::no_case["SQLCODE"]
                            | ascii::no_case["SQL"]
                            | ascii::no_case["SPACE"]
                            | ascii::no_case["SOME"]
                            | ascii::no_case["SMALLINT"]
                            | ascii::no_case["SIZE"]
                            | ascii::no_case["SET"];

    SQL_reserved_word_03 %= ascii::no_case["SESSION_USER"]
                            | ascii::no_case["SESSION"]
                            | ascii::no_case["SELECT"]
                            | ascii::no_case["SECTION"]
                            | ascii::no_case["SECOND"]
                            | ascii::no_case["SCROLL"]
                            | ascii::no_case["SCHEMA"]
                            | ascii::no_case["ROWS"]
                            | ascii::no_case["ROLLBACK"]
                            | ascii::no_case["RIGHT"]
                            | ascii::no_case["REVOKE"]
                            | ascii::no_case["RESTRICT"]
                            | ascii::no_case["RELATIVE"]
                            | ascii::no_case["REFERENCES"]
                            | ascii::no_case["REAL"]
                            | ascii::no_case["READ"];

    SQL_reserved_word_10 %= ascii::no_case["PUBLIC"]
                            | ascii::no_case["PROCEDURE"]
                            | ascii::no_case["PRIVILEGES"]
                            | ascii::no_case["PRIOR"]
                            | ascii::no_case["PRIMARY"]
                            | ascii::no_case["PRESERVE"]
                            | ascii::no_case["PREPARE"]
                            | ascii::no_case["PRECISION"]
                            | ascii::no_case["POSITION"]
                            | ascii::no_case["PARTIAL"]
                            | ascii::no_case["PAD"]
                            | ascii::no_case["OVERLAPS"]
                            | ascii::no_case["OUTPUT"]
                            | ascii::no_case["OUTER"]
                            | ascii::no_case["ORDER"]
                            | ascii::no_case["OR"];

    SQL_reserved_word_11 %= ascii::no_case["OPTION"]
                            | ascii::no_case["OPEN"]
                            | ascii::no_case["ONLY"]
                            | ascii::no_case["ON"]
                            | ascii::no_case["OF"]
                            | ascii::no_case["OCTET_LENGTH"]
                            | ascii::no_case["NUMERIC"]
                            | ascii::no_case["NULLIF"]
                            | ascii::no_case["NULL"]
                            | ascii::no_case["NOT"]
                            | ascii::no_case["NO"]
                            | ascii::no_case["NEXT"]
                            | ascii::no_case["NCHAR"]
                            | ascii::no_case["NATURAL"]
                            | ascii::no_case["NATIONAL"];

    SQL_reserved_word_12 %= ascii::no_case["NAMES"]
                            | ascii::no_case["MONTH"]
                            | ascii::no_case["MODULE"]
                            | ascii::no_case["MINUTE"]
                            | ascii::no_case["MIN"]
                            | ascii::no_case["MAX"]
                            | ascii::no_case["MATCH"]
                            | ascii::no_case["LOWER"]
                            | ascii::no_case["LOCAL"]
                            | ascii::no_case["LIKE"]
                            | ascii::no_case["LEVEL"]
                            | ascii::no_case["LEFT"]
                            | ascii::no_case["LEADING"]
                            | ascii::no_case["LAST"]
                            | ascii::no_case["LANGUAGE"]
                            | ascii::no_case["KEY"];

    SQL_reserved_word_13 %= ascii::no_case["JOIN"]
                            | ascii::no_case["ISOLATION"]
                            | ascii::no_case["IS"]
                            | ascii::no_case["INTO"]
                            | ascii::no_case["INTERVAL"]
                            | ascii::no_case["INTERSECT"]
                            | ascii::no_case["INTEGER"]
                            | ascii::no_case["INT"]
                            | ascii::no_case["INSERT"]
                            | ascii::no_case["INSENSITIVE"]
                            | ascii::no_case["INPUT"]
                            | ascii::no_case["INNER"]
                            | ascii::no_case["INITIALLY"]
                            | ascii::no_case["INDICATOR"]
                            | ascii::no_case["IN"]
                            | ascii::no_case["IMMEDIATE"];

    SQL_reserved_word_20 %= ascii::no_case["IDENTITY"]
                            | ascii::no_case["HOUR"]
                            | ascii::no_case["HAVING"]
                            | ascii::no_case["GROUP"]
                            | ascii::no_case["GRANT"]
                            | ascii::no_case["GOTO"]
                            | ascii::no_case["GO"]
                            | ascii::no_case["GLOBAL"]
                            | ascii::no_case["GET"]
                            | ascii::no_case["FULL"]
                            | ascii::no_case["FROM"]
                            | ascii::no_case["FOUND"]
                            | ascii::no_case["FOREIGN"]
                            | ascii::no_case["FOR"]
                            | ascii::no_case["FLOAT"]
                            | ascii::no_case["FIRST"];

    SQL_reserved_word_21 %= ascii::no_case["FETCH"]
                            | ascii::no_case["FALSE"]
                            | ascii::no_case["EXTRACT"]
                            | ascii::no_case["EXTERNAL"]
                            | ascii::no_case["EXISTS"]
                            | ascii::no_case["EXECUTE"]
                            | ascii::no_case["EXEC"]
                            | ascii::no_case["EXCEPTION"]
                            | ascii::no_case["EXCEPT"]
                            | ascii::no_case["ESCAPE"]
                            | ascii::no_case["END-EXEC"]
                            | ascii::no_case["END"]
                            | ascii::no_case["ELSE"]
                            | ascii::no_case["DROP"]
                            | ascii::no_case["DOUBLE"]
                            | ascii::no_case["DOMAIN"];

    SQL_reserved_word_22 %= ascii::no_case["DISTINCT"]
                            | ascii::no_case["DISCONNECT"]
                            | ascii::no_case["DIAGNOSTICS"]
                            | ascii::no_case["DESCRIPTOR"]
                            | ascii::no_case["DESCRIBE"]
                            | ascii::no_case["DESC"]
                            | ascii::no_case["DELETE"]
                            | ascii::no_case["DEFERRED"]
                            | ascii::no_case["DEFERRABLE"]
                            | ascii::no_case["DEFAULT"]
                            | ascii::no_case["DECLARE"]
                            | ascii::no_case["DECIMAL"]
                            | ascii::no_case["DEALLOCATE"]
                            | ascii::no_case["DAY"]
                            | ascii::no_case["DATE"]
                            | ascii::no_case["CURSOR"];

    SQL_reserved_word_23
        %= ascii::no_case["CURRENT_USER"]
           | ascii::no_case["CURRENT_TIMESTAMP"]
           | ascii::no_case["CURRENT_TIME"]
           | ascii::no_case["CURRENT_DATE"]
           | ascii::no_case["CURRENT"]
           | ascii::no_case["CROSS"]
           | ascii::no_case["CREATE"]
           | ascii::no_case["COUNT"]
           | ascii::no_case["CORRESPONDING"]
           | ascii::no_case["CONVERT"]
           | ascii::no_case["CONTINUE"]
           | ascii::no_case["CONSTRAINTS"]
           | ascii::no_case["CONSTRAINT"]
           | ascii::no_case["CONNECTION"]
           | ascii::no_case["CONNECT"]
           | ascii::no_case["COMMIT"];

    SQL_reserved_word_30
        %= ascii::no_case["COLUMN"]
           | ascii::no_case["COLLATION"]
           | ascii::no_case["COLLATE"]
           | ascii::no_case["COALESCE"]
           | ascii::no_case["CLOSE"]
           | ascii::no_case["CHECK"]
           | ascii::no_case["CHAR_LENGTH"]
           | ascii::no_case["CHARACTER_LENGTH"]
           | ascii::no_case["CHARACTER"]
           | ascii::no_case["CHAR"]
           | ascii::no_case["CATALOG"]
           | ascii::no_case["CAST"]
           | ascii::no_case["CASE"]
           | ascii::no_case["CASCADED"]
           | ascii::no_case["CASCADE"]
           | ascii::no_case["BY"];

    SQL_reserved_word_31 %= ascii::no_case["BOTH"]
                            | ascii::no_case["BIT_LENGTH"]
                            | ascii::no_case["BIT"]
                            | ascii::no_case["BETWEEN"]
                            | ascii::no_case["BEGIN"]
                            | ascii::no_case["AVG"]
                            | ascii::no_case["AUTHORIZATION"]
                            | ascii::no_case["AT"]
                            | ascii::no_case["ASSERTION"]
                            | ascii::no_case["ASC"]
                            | ascii::no_case["AS"]
                            | ascii::no_case["ARE"]
                            | ascii::no_case["ANY"]
                            | ascii::no_case["AND"]
                            | ascii::no_case["ALTER"]
                            | ascii::no_case["ALLOCATE"];

    SQL_reserved_word_32 %= ascii::no_case["ALL"]
                            | ascii::no_case["ADD"]
                            | ascii::no_case["ACTION"]
                            | ascii::no_case["ABSOLUTE"];

    SQL_reserved_word_0 %= SQL_reserved_word_00 | SQL_reserved_word_01
                           | SQL_reserved_word_02 | SQL_reserved_word_03;

    SQL_reserved_word_1 %= SQL_reserved_word_10 | SQL_reserved_word_11
                           | SQL_reserved_word_12 | SQL_reserved_word_13;

    SQL_reserved_word_2 %= SQL_reserved_word_20 | SQL_reserved_word_21
                           | SQL_reserved_word_22 | SQL_reserved_word_23;

    SQL_reserved_word_3 %= SQL_reserved_word_30 | SQL_reserved_word_31
                           | SQL_reserved_word_32;

    SQL_reserved_word %= SQL_reserved_word_0 | SQL_reserved_word_1
                         | SQL_reserved_word_2 | SQL_reserved_word_3;

    keyword %= (SQL_reserved_word | ADQL_reserved_word)
               >> &!(digit | simple_Latin_letter | char_ ("_"));

    simple_Latin_letter %= char_ ("a-zA-Z");
    identifier_character %= digit | simple_Latin_letter | char_ ("_");
    /// nonidentifier_character is to signal that, for example, in an
    /// AND, clause, AND is followed by something that is not an
    /// identifier (e.g. a space or parentheses).
    nonidentifier_character %= char_ - identifier_character;
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

    coord_sys
        %= '\'' >> -ascii::no_case["J2000"]
                                  [at_c<0>(_val)
                                   = ADQL::Coord_Sys::Reference_Frame::J2000]
           >> -ascii::no_case["GEOCENTER"]
                             [at_c<1>(_val)
                              = ADQL::Coord_Sys::Reference_Position::GEOCENTER]
           >> '\'';

    period %= char_ ('.');

    catalog_name %= identifier;
    unqualified_schema_name %= identifier;

    correlation_name %= identifier;
    correlation_specification %= -lexeme[ascii::no_case[ascii::string("AS")]
                                         >> &nonidentifier_character]
      >> correlation_name;

    /// The spec says to have correlation_name as an alternate, but
    /// table_name matches everything that correlation name matches,
    /// so correlation_name will never match.
    qualifier %= table_name;

    /// I have to manually expand the possibilities in
    /// column_reference and table name, because a catalog.schema can
    /// match against schema.table or table.column, gobbling up the
    /// table or column name and making the parse fail.
    table_name %= 
      ("TAP_UPLOAD."
       >> identifier[_val = boost::phoenix::ref(table_mapping)[_1]])
      | hold[catalog_name >> period >> unqualified_schema_name >> period
             >> identifier]
      | hold[unqualified_schema_name >> period >> identifier]
      | identifier;

    column_reference %=
      ("TAP_UPLOAD."
       >> identifier[_val = boost::phoenix::ref(table_mapping)[_1]] >> period >> identifier)
      | hold[catalog_name >> period >> unqualified_schema_name
                             >> period >> identifier >> period >> identifier]
      | hold[unqualified_schema_name >> period >> identifier >> period
             >> identifier]
      | hold[identifier >> period >> identifier]
      | identifier;


    unsigned_integer %= +digit;
    exact_numeric_literal
        %= (unsigned_integer >> -(period >> unsigned_integer))
           | (period >> unsigned_integer);

    sign %= char_ ('+') | char_ ('-');
    signed_integer %= -sign >> unsigned_integer;
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

    nonquote_character %= SQL_language_character - quote;
    character_representation %= nonquote_character | ascii::string ("''");

    comment_introducer %= minus_sign >> +minus_sign;
    comment_character %= nonquote_character | quote;
    comment %= comment_introducer >> *comment_character >> newline;

    separator %= comment | space | newline;

    character_string_literal
        %= quote >> *character_representation >> quote
           >> *hold[+separator >> quote >> *character_representation >> quote];

    general_literal %= character_string_literal;
    unsigned_literal %= unsigned_numeric_literal | general_literal;
    unsigned_value_specification %= unsigned_literal;

    set_function_type %= ascii::no_case[ascii::string ("AVG")]
                         | ascii::no_case[ascii::string ("MAX")]
                         | ascii::no_case[ascii::string ("MIN")]
                         | ascii::no_case[ascii::string ("SUM")]
                         | ascii::no_case[ascii::string ("COUNT")];
    /// This is a little funky because we need to preserve the space
    /// between the set_quantifier and whatever follows it.
    set_quantifier %= hold[(ascii::no_case[ascii::string ("DISTINCT")]
                            | ascii::no_case[ascii::string ("ALL")])
                           >> &(space | tab | newline)];

    general_set_function %= set_function_type >> char_ ('(') >> -set_quantifier
                            >> value_expression >> char_ (')');

    set_function_specification
        %= hold[ascii::no_case[ascii::string ("COUNT")] >> char_ ('(')
                >> char_ ('*') >> char_ (')')] | general_set_function;

    value_expression_primary
        %= unsigned_value_specification | column_reference
           | set_function_specification
           | (char_ ('(') >> value_expression >> char_ (')'));

    trig_function
        %= (hold[(ascii::no_case[ascii::string ("ACOS")]
                  | ascii::no_case[ascii::string ("ASIN")]
                  | ascii::no_case[ascii::string ("ATAN")]
                  | ascii::no_case[ascii::string ("COS")]
                  | ascii::no_case[ascii::string ("COT")]
                  | ascii::no_case[ascii::string ("SIN")]
                  | ascii::no_case[ascii::string ("TAN")]) >> char_ ('(')]
            >> numeric_value_expression >> char_ (')'))
           | (hold[ascii::no_case[ascii::string ("ATAN2")] >> char_ ('(')]
              >> numeric_value_expression >> char_ (',')
              >> numeric_value_expression >> char_ (')'));

    math_function
        %= (hold[(ascii::no_case[ascii::string ("ABS")]
                  | ascii::no_case[ascii::string ("CEILING")]
                  | ascii::no_case[ascii::string ("DEGREES")]
                  | ascii::no_case[ascii::string ("EXP")]
                  | ascii::no_case[ascii::string ("FLOOR")]
                  | ascii::no_case[ascii::string ("LOG10")]
                  | ascii::no_case[ascii::string ("LOG")]
                  | ascii::no_case[ascii::string ("RADIANS")]
                  | ascii::no_case[ascii::string ("SQRT")]) >> char_ ('(')]
            >> numeric_value_expression >> char_ (')'))
           | (hold[(ascii::no_case[ascii::string ("MOD")]
                    | ascii::no_case[ascii::string ("POWER")]) >> char_ ('(')]
              >> numeric_value_expression >> char_ (',')
              >> numeric_value_expression >> char_ (')'))
           | (hold[ascii::no_case[ascii::string ("PI")] >> char_ ('(')]
              >> char_ (')'))
           | (hold[ascii::no_case[ascii::string ("RAND")] >> char_ ('(')]
              >> -numeric_value_expression >> char_ (')'))
           | (hold[(ascii::no_case[ascii::string ("ROUND")]
                    | ascii::no_case[ascii::string ("TRUNCATE")])
                   >> char_ ('(')] >> numeric_value_expression
              >> -(char_ (',') >> signed_integer) >> char_ (')'));

    /// default_function_prefix is a bit useless since it is optional.
    default_function_prefix %= ascii::string ("udf_");
    user_defined_function_name %= -default_function_prefix
                                  >> regular_identifier;
    user_defined_function_param %= value_expression;
    user_defined_function
        %= hold[user_defined_function_name >> char_ ('(')]
           /// Use this awkward syntax instead of the usual list parser so
           /// that the attribute is still a string overall.
           >> -(user_defined_function_param
                >> *(char_ (',') >> user_defined_function_param))
           >> char_ (')');

    // FIXME: numeric_value_function should have
    // numeric_geometry_function
    numeric_value_function %= trig_function | math_function
                              | user_defined_function;
    /// Flipped the order here, because a value_expression can match a
    /// function name.
    numeric_primary %= numeric_value_function | value_expression_primary;
    factor %= -sign >> numeric_primary;

    /// This puts term and numeric_value_expression on the left, not
    /// right.  Otherwise the rule greedily recurses on itself and
    /// runs out of stack space.  With that reordering, the first term
    /// is always the same and the second part becomes optional.
    term %= factor >> -(char_ ("*/") >> term);
    numeric_value_expression %= term
                                >> -(char_ ("+-") >> numeric_value_expression);

    // FIXME: string_value_function should have a string_geometry_function;
    string_value_function %= user_defined_function;
    /// Flipped the order here because a value_expression_primary can
    /// match a function name that should be matched by
    /// string_value_function
    character_primary %= string_value_function | value_expression_primary;
    character_factor %= character_primary;
    concatenation_operator %= ascii::string ("||");
    /// Flip the order of character_factor and
    /// character_value_expression to prevent recursion.
    character_value_expression
        %= character_factor
           >> -(concatenation_operator >> character_value_expression);

    string_value_expression %= character_value_expression;
    // FIXME: value_expression should also have a
    // geometry_value_expression, but the database can not handle it.

    /// This expression first checks for a concatenation operator.
    /// Otherwise a numeric_value_expression would match the first
    /// half of a concatenation, meaning the concatenation operator
    /// would cause the parse to fail.  We can not put
    /// string_value_expression first, because that would partially
    /// match arithmetic.  For 'a+b', it matches 'a' but not the '+'.
    value_expression %= (hold[character_factor >> concatenation_operator]
                         >> character_value_expression)
                        | numeric_value_expression | string_value_expression;

    coord %= numeric_value_expression >> ',' >> numeric_value_expression;
    point %= ascii::no_case["POINT"] >> '(' >> coord_sys >> ',' >> coord
             >> ')';

    // FIXME: In theory, the radius should be an expression, not a
    // number.  In practice, we can only handle numbers.
    circle %= ascii::no_case["CIRCLE"] >> '(' >> coord_sys >> ',' >> coord
              >> ',' >> boost::spirit::qi::double_ >> ')';
    ellipse %= ascii::no_case["ELLIPSE"] >> '(' >> coord_sys >> ',' >> coord
               >> ',' >> boost::spirit::qi::double_ >> ','
               >> boost::spirit::qi::double_ >> ','
               >> boost::spirit::qi::double_ >> ')';
    box %= ascii::no_case["BOX"] >> '(' >> coord_sys >> ',' >> coord >> ','
           >> boost::spirit::qi::double_ >> ',' >> boost::spirit::qi::double_
           >> ')';
    coord_list %= coord % ',';
    polygon %= ascii::no_case["POLYGON"] >> '(' >> coord_sys >> ','
               >> coord_list >> ')';

    shape %= circle | box | ellipse | polygon;
    contains %= ascii::no_case["CONTAINS"] >> '(' >> point >> ',' >> shape
                >> ')';

    geometry %= (contains >> '=' >> '1') | (lit ('1') >> '=' >> contains);

    column_name %= identifier;

    as %= value_expression
          >> lexeme[ascii::no_case["AS"] >> &nonidentifier_character]
          >> column_name;

    select_non_as_item %= hold[qualifier >> ascii::string (".*")]
      | value_expression;
    select_item %= as | select_non_as_item;
    select_list %= select_item % ',';
    columns %= ascii::string ("*") | select_list;

    table_reference %=
      (table_name >> -correlation_specification);
    // FIXME: table_reference is supposed to include derived_table and joined_table
    // | (derived_table >> correlation_specification)
    // | joined_table;

    from_clause %= lexeme[ascii::no_case["FROM"] >> &nonidentifier_character]
      >> table_reference % ",";

    comparison_predicate %= value_expression
                            >> (ascii::string ("=") | ascii::string ("!=")
                                | ascii::string ("<>") | ascii::string ("<=")
                                | ascii::string (">=") | ascii::string ("<")
                                | ascii::string (">")) >> value_expression;

    between_predicate
        %= value_expression
           >> lexeme[-(ascii::no_case[ascii::string ("NOT")]
                       >> boost::spirit::qi::space)
                     >> ascii::no_case["BETWEEN"] >> &nonidentifier_character]
           >> value_expression
           >> lexeme[ascii::no_case["AND"] >> &nonidentifier_character]
           >> value_expression;

    in_predicate
        %= value_expression
           >> lexeme[-(ascii::no_case[ascii::string ("NOT")]
                       >> boost::spirit::qi::space) >> ascii::no_case["IN"]
                     >> &nonidentifier_character]
           // FIXME: This should be table_subquery, not value_expression
           >> (value_expression
               | (lit ('(') >> (value_expression % ',') >> ')'));

    null_predicate
        %= value_expression
           >> lexeme[ascii::no_case["IS"] >> &boost::spirit::qi::space]
           >> -lexeme[ascii::no_case[ascii::string ("NOT")]
                      >> &boost::spirit::qi::space] >> ascii::no_case["NULL"];

    match_value %= character_value_expression;
    pattern %= character_value_expression;

    like_predicate
        %= match_value >> -lexeme[ascii::no_case[ascii::string ("NOT")]
                                  >> &boost::spirit::qi::space]
           >> lexeme[ascii::no_case["LIKE"] >> &boost::spirit::qi::space]
           >> pattern;

    // FIXME: add exists
    predicate %= (comparison_predicate | between_predicate | in_predicate
                  | null_predicate | like_predicate);

    boolean_primary %= predicate | (lit ('(') >> search_condition >> ')');

    boolean_factor %= lexeme[-(ascii::no_case[ascii::string ("NOT")]
                               >> &nonidentifier_character)]
                      >> boolean_primary;

    boolean_term %= boolean_factor
                    >> lexeme[(ascii::no_case[ascii::string ("AND")]
                               | ascii::no_case[ascii::string ("OR")])
                              >> &nonidentifier_character] >> search_condition;

    search_condition
        = (boolean_term | boolean_factor)[push_back (at_c<0>(_val), _1)];

    where
        = lexeme[ascii::no_case["WHERE"] >> &nonidentifier_character]
          >> ((geometry[at_c<0>(_val) = _1]
               >> -(ascii::no_case["AND"] >> '('
                    >> search_condition[at_c<1>(_val) = _1] >> ')'))
              | (lit ('(') >> search_condition[at_c<1>(_val) = _1] >> ')'
                 >> (lexeme[ascii::no_case["AND"] >> &nonidentifier_character]
                     >> geometry[at_c<0>(_val) = _1]))
              | (search_condition[at_c<1>(_val) = _1]));

    grouping_column_reference %= column_reference;
    grouping_column_reference_list %= grouping_column_reference
                                      >> *(char_ (',') >> column_reference);
    group_by_clause
        %= lexeme[ascii::no_case["GROUP"] >> &boost::spirit::qi::space]
           >> lexeme[ascii::no_case["BY"] >> &nonidentifier_character]
           >> grouping_column_reference_list;

    having_clause
        %= lexeme[ascii::no_case["HAVING"] >> &nonidentifier_character]
           >> search_condition;

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
        %= lexeme[ascii::no_case["ORDER"] >> &boost::spirit::qi::space]
           >> lexeme[ascii::no_case["BY"] >> &boost::spirit::qi::space]
           >> sort_specification_list;

    query %= lexeme[ascii::no_case["SELECT"] >> &nonidentifier_character]
             >> -set_quantifier
             >> -(lexeme[ascii::no_case["TOP"] >> &boost::spirit::qi::space]
                  >> ulong_long) >> columns
             >> from_clause >> (-where) >> (-group_by_clause)
             >> (-having_clause) >> (-order_by_clause);
  }

  std::map<std::string,std::string> table_mapping;

  boost::spirit::qi::rule<Iterator, char()> simple_Latin_letter,
      identifier_character, nonidentifier_character, SQL_language_character,
      SQL_special_character, nondoublequote_character, quote, space, newline,
      tab, minus_sign, nonquote_character, sign, period;

  boost::spirit::qi::rule<Iterator, std::string ()> unsigned_integer,
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
      concatenation_operator;

  boost::spirit::qi::rule<Iterator, std::string (),
                          boost::spirit::ascii::space_type> column_reference,
      qualifier, correlation_name, table_name,
      unqualified_schema_name, catalog_name, general_literal, unsigned_literal,
      unsigned_value_specification, set_function_type, general_set_function,
      set_function_specification, value_expression_primary, value_expression,
      numeric_value_expression, numeric_primary, factor, term,
      numeric_value_function, trig_function, math_function,
      user_defined_function, user_defined_function_name,
      user_defined_function_param, default_function_prefix,
      grouping_column_reference, grouping_column_reference_list,
      group_by_clause, sort_specification_list, order_by_clause,
      string_value_function, character_primary, character_factor,
      character_value_expression, match_value, pattern,
      string_value_expression, select_non_as_item, from_clause, table_reference,
      correlation_specification;

  boost::spirit::qi::rule<Iterator, ADQL::Coord_Sys (),
                          boost::spirit::ascii::space_type> coord_sys;
  boost::spirit::qi::rule<Iterator, ADQL::Coordinate (),
                          boost::spirit::ascii::space_type> coord;

  boost::spirit::qi::rule<Iterator, ADQL::Query::Column_Variant (),
                          boost::spirit::ascii::space_type> select_item;

  boost::spirit::qi::rule<Iterator, std::vector<ADQL::Query::Column_Variant>(),
                          boost::spirit::ascii::space_type> select_list;

  boost::spirit::qi::rule<Iterator, ADQL::Query::Columns (),
                          boost::spirit::ascii::space_type> columns;

  boost::spirit::qi::rule<Iterator, ADQL::As (),
                          boost::spirit::ascii::space_type> as;

  boost::spirit::qi::rule<Iterator, ADQL::Point (),
                          boost::spirit::ascii::space_type> point;
  boost::spirit::qi::rule<Iterator, ADQL::Circle (),
                          boost::spirit::ascii::space_type> circle;
  boost::spirit::qi::rule<Iterator, ADQL::Ellipse (),
                          boost::spirit::ascii::space_type> ellipse;
  boost::spirit::qi::rule<Iterator, ADQL::Box (),
                          boost::spirit::ascii::space_type> box;
  boost::spirit::qi::rule<Iterator, ADQL::Polygon (),
                          boost::spirit::ascii::space_type> polygon;
  boost::spirit::qi::rule<Iterator, std::vector<ADQL::Coordinate>(),
                          boost::spirit::ascii::space_type> coord_list;

  boost::spirit::qi::rule<Iterator, ADQL::Contains (),
                          boost::spirit::ascii::space_type> contains;
  boost::spirit::qi::rule<Iterator, ADQL::Contains::Shape (),
                          boost::spirit::ascii::space_type> shape;

  boost::spirit::qi::rule<Iterator, ADQL::Geometry (),
                          boost::spirit::ascii::space_type> geometry;

  boost::spirit::qi::rule<Iterator, ADQL::Comparison_Predicate (),
                          boost::spirit::ascii::space_type>
  comparison_predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Between_Predicate (),
                          boost::spirit::ascii::space_type> between_predicate;

  boost::spirit::qi::rule<Iterator, ADQL::In_Predicate (),
                          boost::spirit::ascii::space_type> in_predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Null_Predicate (),
                          boost::spirit::ascii::space_type> null_predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Like_Predicate (),
                          boost::spirit::ascii::space_type> like_predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Predicate (),
                          boost::spirit::ascii::space_type> predicate;

  boost::spirit::qi::rule<Iterator, ADQL::Boolean_Primary (),
                          boost::spirit::ascii::space_type> boolean_primary;

  boost::spirit::qi::rule<Iterator, ADQL::Boolean_Factor (),
                          boost::spirit::ascii::space_type> boolean_factor;

  boost::spirit::qi::rule<Iterator, ADQL::Boolean_Term (),
                          boost::spirit::ascii::space_type> boolean_term;

  boost::spirit::qi::rule<Iterator, ADQL::Search_Condition (),
                          boost::spirit::ascii::space_type> search_condition;

  boost::spirit::qi::rule<Iterator, ADQL::Having (),
                          boost::spirit::ascii::space_type> having_clause;

  boost::spirit::qi::rule<Iterator, ADQL::Where (),
                          boost::spirit::ascii::space_type> where;

  boost::spirit::qi::rule<Iterator, ADQL::Query (),
                          boost::spirit::ascii::space_type> query;
};
