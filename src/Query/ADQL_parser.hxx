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
  ADQL_parser () : ADQL_parser::base_type (query)
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
    ADQL_reserved_word %= ascii::no_case[ascii::string ("TRUNCATE")]
                          | ascii::no_case[ascii::string ("TOP")]
                          | ascii::no_case[ascii::string ("TAN")]
                          | ascii::no_case[ascii::string ("SQRT")]
                          | ascii::no_case[ascii::string ("SIN")]
                          | ascii::no_case[ascii::string ("ROUND")]
                          | ascii::no_case[ascii::string ("REGION")]
                          | ascii::no_case[ascii::string ("RAND")]
                          | ascii::no_case[ascii::string ("RADIANS")]
                          | ascii::no_case[ascii::string ("POWER")]
                          | ascii::no_case[ascii::string ("POLYGON")]
                          | ascii::no_case[ascii::string ("POINT")]
                          | ascii::no_case[ascii::string ("PI")]
                          | ascii::no_case[ascii::string ("MOD")]
                          | ascii::no_case[ascii::string ("LOG10")]
                          | ascii::no_case[ascii::string ("LOG")]
                          | ascii::no_case[ascii::string ("INTERSECTS")]
                          | ascii::no_case[ascii::string ("FLOOR")]
                          | ascii::no_case[ascii::string ("EXP")]
                          | ascii::no_case[ascii::string ("DISTANCE")]
                          | ascii::no_case[ascii::string ("DEGREES")]
                          | ascii::no_case[ascii::string ("COS")]
                          | ascii::no_case[ascii::string ("COORDSYS")]
                          | ascii::no_case[ascii::string ("COORD2")]
                          | ascii::no_case[ascii::string ("COORD1")]
                          | ascii::no_case[ascii::string ("CONTAINS")]
                          | ascii::no_case[ascii::string ("CIRCLE")]
                          | ascii::no_case[ascii::string ("CENTROID")]
                          | ascii::no_case[ascii::string ("CEILING")]
                          | ascii::no_case[ascii::string ("BOX")]
                          | ascii::no_case[ascii::string ("ATAN2")]
                          | ascii::no_case[ascii::string ("ATAN")]
                          | ascii::no_case[ascii::string ("ASIN")]
                          | ascii::no_case[ascii::string ("AREA")]
                          | ascii::no_case[ascii::string ("ACOS")]
                          | ascii::no_case[ascii::string ("ABS")];

    SQL_reserved_word %= ascii::no_case[ascii::string ("ZONE")]
                         | ascii::no_case[ascii::string ("YEAR")]
                         | ascii::no_case[ascii::string ("WRITE")]
                         | ascii::no_case[ascii::string ("WORK")]
                         | ascii::no_case[ascii::string ("WITH")]
                         | ascii::no_case[ascii::string ("WHERE")]
                         | ascii::no_case[ascii::string ("WHENEVER")]
                         | ascii::no_case[ascii::string ("WHEN")]
                         | ascii::no_case[ascii::string ("VIEW")]
                         | ascii::no_case[ascii::string ("VARYING")]
                         | ascii::no_case[ascii::string ("VARCHAR")]
                         | ascii::no_case[ascii::string ("VALUES")]
                         | ascii::no_case[ascii::string ("VALUE")]
                         | ascii::no_case[ascii::string ("USING")]
                         | ascii::no_case[ascii::string ("USER")]
                         | ascii::no_case[ascii::string ("USAGE")]
                         | ascii::no_case[ascii::string ("UPPER")]
                         | ascii::no_case[ascii::string ("UPDATE")]
                         | ascii::no_case[ascii::string ("UNKNOWN")]
                         | ascii::no_case[ascii::string ("UNIQUE")]
                         | ascii::no_case[ascii::string ("UNION")]
                         | ascii::no_case[ascii::string ("TRUE")]
                         | ascii::no_case[ascii::string ("TRIM")]
                         | ascii::no_case[ascii::string ("TRANSLATION")]
                         | ascii::no_case[ascii::string ("TRANSLATE")]
                         | ascii::no_case[ascii::string ("TRANSACTION")]
                         | ascii::no_case[ascii::string ("TRAILING")]
                         | ascii::no_case[ascii::string ("TO")]
                         | ascii::no_case[ascii::string ("TIMEZONE_MINUTE")]
                         | ascii::no_case[ascii::string ("TIMEZONE_HOUR")]
                         | ascii::no_case[ascii::string ("TIMESTAMP")]
                         | ascii::no_case[ascii::string ("TIME")]
                         | ascii::no_case[ascii::string ("THEN")]
                         | ascii::no_case[ascii::string ("TEMPORARY")]
                         | ascii::no_case[ascii::string ("TABLE")]
                         | ascii::no_case[ascii::string ("SYSTEM_USER")]
                         | ascii::no_case[ascii::string ("SUM")]
                         | ascii::no_case[ascii::string ("SUBSTRING")]
                         | ascii::no_case[ascii::string ("SQLSTATE")]
                         | ascii::no_case[ascii::string ("SQLERROR")]
                         | ascii::no_case[ascii::string ("SQLCODE")]
                         | ascii::no_case[ascii::string ("SQL")]
                         | ascii::no_case[ascii::string ("SPACE")]
                         | ascii::no_case[ascii::string ("SOME")]
                         | ascii::no_case[ascii::string ("SMALLINT")]
                         | ascii::no_case[ascii::string ("SIZE")]
                         | ascii::no_case[ascii::string ("SET")]
                         | ascii::no_case[ascii::string ("SESSION_USER")]
                         | ascii::no_case[ascii::string ("SESSION")]
                         | ascii::no_case[ascii::string ("SELECT")]
                         | ascii::no_case[ascii::string ("SECTION")]
                         | ascii::no_case[ascii::string ("SECOND")]
                         | ascii::no_case[ascii::string ("SCROLL")]
                         | ascii::no_case[ascii::string ("SCHEMA")]
                         | ascii::no_case[ascii::string ("ROWS")]
                         | ascii::no_case[ascii::string ("ROLLBACK")]
                         | ascii::no_case[ascii::string ("RIGHT")]
                         | ascii::no_case[ascii::string ("REVOKE")]
                         | ascii::no_case[ascii::string ("RESTRICT")]
                         | ascii::no_case[ascii::string ("RELATIVE")]
                         | ascii::no_case[ascii::string ("REFERENCES")]
                         | ascii::no_case[ascii::string ("REAL")]
                         | ascii::no_case[ascii::string ("READ")]
                         | ascii::no_case[ascii::string ("PUBLIC")]
                         | ascii::no_case[ascii::string ("PROCEDURE")]
                         | ascii::no_case[ascii::string ("PRIVILEGES")]
                         | ascii::no_case[ascii::string ("PRIOR")]
                         | ascii::no_case[ascii::string ("PRIMARY")]
                         | ascii::no_case[ascii::string ("PRESERVE")]
                         | ascii::no_case[ascii::string ("PREPARE")]
                         | ascii::no_case[ascii::string ("PRECISION")]
                         | ascii::no_case[ascii::string ("POSITION")]
                         | ascii::no_case[ascii::string ("PARTIAL")]
                         | ascii::no_case[ascii::string ("PAD")]
                         | ascii::no_case[ascii::string ("OVERLAPS")]
                         | ascii::no_case[ascii::string ("OUTPUT")]
                         | ascii::no_case[ascii::string ("OUTER")]
                         | ascii::no_case[ascii::string ("ORDER")]
                         | ascii::no_case[ascii::string ("OR")]
                         | ascii::no_case[ascii::string ("OPTION")]
                         | ascii::no_case[ascii::string ("OPEN")]
                         | ascii::no_case[ascii::string ("ONLY")]
                         | ascii::no_case[ascii::string ("ON")]
                         | ascii::no_case[ascii::string ("OF")]
                         | ascii::no_case[ascii::string ("OCTET_LENGTH")]
                         | ascii::no_case[ascii::string ("NUMERIC")]
                         | ascii::no_case[ascii::string ("NULLIF")]
                         | ascii::no_case[ascii::string ("NULL")]
                         | ascii::no_case[ascii::string ("NOT")]
                         | ascii::no_case[ascii::string ("NO")]
                         | ascii::no_case[ascii::string ("NEXT")]
                         | ascii::no_case[ascii::string ("NCHAR")]
                         | ascii::no_case[ascii::string ("NATURAL")]
                         | ascii::no_case[ascii::string ("NATIONAL")]
                         | ascii::no_case[ascii::string ("NAMES")]
                         | ascii::no_case[ascii::string ("MONTH")]
                         | ascii::no_case[ascii::string ("MODULE")]
                         | ascii::no_case[ascii::string ("MINUTE")]
                         | ascii::no_case[ascii::string ("MIN")]
                         | ascii::no_case[ascii::string ("MAX")]
                         | ascii::no_case[ascii::string ("MATCH")]
                         | ascii::no_case[ascii::string ("LOWER")]
                         | ascii::no_case[ascii::string ("LOCAL")]
                         | ascii::no_case[ascii::string ("LIKE")]
                         | ascii::no_case[ascii::string ("LEVEL")]
                         | ascii::no_case[ascii::string ("LEFT")]
                         | ascii::no_case[ascii::string ("LEADING")]
                         | ascii::no_case[ascii::string ("LAST")]
                         | ascii::no_case[ascii::string ("LANGUAGE")]
                         | ascii::no_case[ascii::string ("KEY")]
                         | ascii::no_case[ascii::string ("JOIN")]
                         | ascii::no_case[ascii::string ("ISOLATION")]
                         | ascii::no_case[ascii::string ("IS")]
                         | ascii::no_case[ascii::string ("INTO")]
                         | ascii::no_case[ascii::string ("INTERVAL")]
                         | ascii::no_case[ascii::string ("INTERSECT")]
                         | ascii::no_case[ascii::string ("INTEGER")]
                         | ascii::no_case[ascii::string ("INT")]
                         | ascii::no_case[ascii::string ("INSERT")]
                         | ascii::no_case[ascii::string ("INSENSITIVE")]
                         | ascii::no_case[ascii::string ("INPUT")]
                         | ascii::no_case[ascii::string ("INNER")]
                         | ascii::no_case[ascii::string ("INITIALLY")]
                         | ascii::no_case[ascii::string ("INDICATOR")]
                         | ascii::no_case[ascii::string ("IN")]
                         | ascii::no_case[ascii::string ("IMMEDIATE")]
                         | ascii::no_case[ascii::string ("IDENTITY")]
                         | ascii::no_case[ascii::string ("HOUR")]
                         | ascii::no_case[ascii::string ("HAVING")]
                         | ascii::no_case[ascii::string ("GROUP")]
                         | ascii::no_case[ascii::string ("GRANT")]
                         | ascii::no_case[ascii::string ("GOTO")]
                         | ascii::no_case[ascii::string ("GO")]
                         | ascii::no_case[ascii::string ("GLOBAL")]
                         | ascii::no_case[ascii::string ("GET")]
                         | ascii::no_case[ascii::string ("FULL")]
                         | ascii::no_case[ascii::string ("FROM")]
                         | ascii::no_case[ascii::string ("FOUND")]
                         | ascii::no_case[ascii::string ("FOREIGN")]
                         | ascii::no_case[ascii::string ("FOR")]
                         | ascii::no_case[ascii::string ("FLOAT")]
                         | ascii::no_case[ascii::string ("FIRST")]
                         | ascii::no_case[ascii::string ("FETCH")]
                         | ascii::no_case[ascii::string ("FALSE")]
                         | ascii::no_case[ascii::string ("EXTRACT")]
                         | ascii::no_case[ascii::string ("EXTERNAL")]
                         | ascii::no_case[ascii::string ("EXISTS")]
                         | ascii::no_case[ascii::string ("EXECUTE")]
                         | ascii::no_case[ascii::string ("EXEC")]
                         | ascii::no_case[ascii::string ("EXCEPTION")]
                         | ascii::no_case[ascii::string ("EXCEPT")]
                         | ascii::no_case[ascii::string ("ESCAPE")]
                         | ascii::no_case[ascii::string ("END-EXEC")]
                         | ascii::no_case[ascii::string ("END")]
                         | ascii::no_case[ascii::string ("ELSE")]
                         | ascii::no_case[ascii::string ("DROP")]
                         | ascii::no_case[ascii::string ("DOUBLE")]
                         | ascii::no_case[ascii::string ("DOMAIN")]
                         | ascii::no_case[ascii::string ("DISTINCT")]
                         | ascii::no_case[ascii::string ("DISCONNECT")]
                         | ascii::no_case[ascii::string ("DIAGNOSTICS")]
                         | ascii::no_case[ascii::string ("DESCRIPTOR")]
                         | ascii::no_case[ascii::string ("DESCRIBE")]
                         | ascii::no_case[ascii::string ("DESC")]
                         | ascii::no_case[ascii::string ("DELETE")]
                         | ascii::no_case[ascii::string ("DEFERRED")]
                         | ascii::no_case[ascii::string ("DEFERRABLE")]
                         | ascii::no_case[ascii::string ("DEFAULT")]
                         | ascii::no_case[ascii::string ("DECLARE")]
                         | ascii::no_case[ascii::string ("DECIMAL")]
                         | ascii::no_case[ascii::string ("DEALLOCATE")]
                         | ascii::no_case[ascii::string ("DAY")]
                         | ascii::no_case[ascii::string ("DATE")]
                         | ascii::no_case[ascii::string ("CURSOR")]
                         | ascii::no_case[ascii::string ("CURRENT_USER")]
                         | ascii::no_case[ascii::string ("CURRENT_TIMESTAMP")]
                         | ascii::no_case[ascii::string ("CURRENT_TIME")]
                         | ascii::no_case[ascii::string ("CURRENT_DATE")]
                         | ascii::no_case[ascii::string ("CURRENT")]
                         | ascii::no_case[ascii::string ("CROSS")]
                         | ascii::no_case[ascii::string ("CREATE")]
                         | ascii::no_case[ascii::string ("COUNT")]
                         | ascii::no_case[ascii::string ("CORRESPONDING")]
                         | ascii::no_case[ascii::string ("CONVERT")]
                         | ascii::no_case[ascii::string ("CONTINUE")]
                         | ascii::no_case[ascii::string ("CONSTRAINTS")]
                         | ascii::no_case[ascii::string ("CONSTRAINT")]
                         | ascii::no_case[ascii::string ("CONNECTION")]
                         | ascii::no_case[ascii::string ("CONNECT")]
                         | ascii::no_case[ascii::string ("COMMIT")]
                         | ascii::no_case[ascii::string ("COLUMN")]
                         | ascii::no_case[ascii::string ("COLLATION")]
                         | ascii::no_case[ascii::string ("COLLATE")]
                         | ascii::no_case[ascii::string ("COALESCE")]
                         | ascii::no_case[ascii::string ("CLOSE")]
                         | ascii::no_case[ascii::string ("CHECK")]
                         | ascii::no_case[ascii::string ("CHAR_LENGTH")]
                         | ascii::no_case[ascii::string ("CHARACTER_LENGTH")]
                         | ascii::no_case[ascii::string ("CHARACTER")]
                         | ascii::no_case[ascii::string ("CHAR")]
                         | ascii::no_case[ascii::string ("CATALOG")]
                         | ascii::no_case[ascii::string ("CAST")]
                         | ascii::no_case[ascii::string ("CASE")]
                         | ascii::no_case[ascii::string ("CASCADED")]
                         | ascii::no_case[ascii::string ("CASCADE")]
                         | ascii::no_case[ascii::string ("BY")]
                         | ascii::no_case[ascii::string ("BOTH")]
                         | ascii::no_case[ascii::string ("BIT_LENGTH")]
                         | ascii::no_case[ascii::string ("BIT")]
                         | ascii::no_case[ascii::string ("BETWEEN")]
                         | ascii::no_case[ascii::string ("BEGIN")]
                         | ascii::no_case[ascii::string ("AVG")]
                         | ascii::no_case[ascii::string ("AUTHORIZATION")]
                         | ascii::no_case[ascii::string ("AT")]
                         | ascii::no_case[ascii::string ("ASSERTION")]
                         | ascii::no_case[ascii::string ("ASC")]
                         | ascii::no_case[ascii::string ("AS")]
                         | ascii::no_case[ascii::string ("ARE")]
                         | ascii::no_case[ascii::string ("ANY")]
                         | ascii::no_case[ascii::string ("AND")]
                         | ascii::no_case[ascii::string ("ALTER")]
                         | ascii::no_case[ascii::string ("ALLOCATE")]
                         | ascii::no_case[ascii::string ("ALL")]
                         | ascii::no_case[ascii::string ("ADD")]
                         | ascii::no_case[ascii::string ("ACTION")]
                         | ascii::no_case[ascii::string ("ABSOLUTE")];

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
    schema_name %= -(hold[catalog_name >> period]) >> unqualified_schema_name;
    table_name %= -(hold[schema_name >> period]) >> identifier;
    correlation_name %= identifier;

    /// The spec says to have correlation_name as an alternate, but
    /// table_name matches everything that correlation name matches,
    /// so correlation_name will never match.
    qualifier %= table_name;

    column_reference %= -(hold[qualifier >> period]) >> identifier;

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
           >> *(+separator >> quote >> *character_representation >> quote);

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
              >> ',' >> boost::spirit::qi::double_
              >> ',' >> boost::spirit::qi::double_
              >> ',' >> boost::spirit::qi::double_ >> ')';
    box %= ascii::no_case["BOX"] >> '(' >> coord_sys >> ',' >> coord
              >> ',' >> boost::spirit::qi::double_
              >> ',' >> boost::spirit::qi::double_ >> ')';
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

    comparison_predicate %= value_expression
                            >> (ascii::string ("=") | ascii::string ("!=")
                                | ascii::string ("<>")
                                | ascii::string ("<=") | ascii::string (">=")
                                | ascii::string ("<") | ascii::string (">")
                                ) >> value_expression;

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
             >> lexeme[ascii::no_case["FROM"] >> &nonidentifier_character]
             // FIXME: should be a table_reference
             >> identifier >> (-where) >> (-group_by_clause)
             >> (-having_clause) >> (-order_by_clause);
  }

  boost::spirit::qi::rule<Iterator, char()> simple_Latin_letter,
      identifier_character, nonidentifier_character, SQL_language_character,
      SQL_special_character, nondoublequote_character, quote, space, newline,
      tab, minus_sign, nonquote_character, sign, period;

  boost::spirit::qi::rule<Iterator, std::string ()> unsigned_integer,
      exact_numeric_literal, signed_integer, mantissa, exponent,
      approximate_numeric_literal, unsigned_numeric_literal, comment,
      comment_introducer, comment_character, delimited_identifier,
      delimited_identifier_part, delimited_identifier_body,
      character_representation, ADQL_reserved_word, SQL_reserved_word, keyword,
      all_identifiers, regular_identifier, identifier, set_quantifier,
      character_string_literal, separator, column_name, sort_key,
      ordering_specification, sort_specification, concatenation_operator;

  boost::spirit::qi::rule<Iterator, std::string (),
                          boost::spirit::ascii::space_type> column_reference,
      qualifier, correlation_name, table_name, schema_name,
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
      string_value_expression, select_non_as_item;

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
  boost::spirit::qi::rule<Iterator, ADQL::Contains::Shape(),
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
