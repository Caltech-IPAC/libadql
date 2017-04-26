#include "../../ADQL_parser.hxx"

void ADQL_parser::init_reserved_words ()
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
  ADQL_reserved_word %= ascii::no_case["TRUNCATE"] | ascii::no_case["TOP"]
                        | ascii::no_case["TAP_UPLOAD"] | ascii::no_case["TAN"]
                        | ascii::no_case["SQRT"] | ascii::no_case["SIN"]
                        | ascii::no_case["ROUND"] | ascii::no_case["REGION"]
                        | ascii::no_case["RAND"] | ascii::no_case["RADIANS"]
                        | ascii::no_case["POWER"] | ascii::no_case["POLYGON"]
                        | ascii::no_case["POINT"] | ascii::no_case["PI"]
                        | ascii::no_case["MOD"] | ascii::no_case["LOG10"]
                        | ascii::no_case["LOG"] | ascii::no_case["INTERSECTS"]
                        | ascii::no_case["FLOOR"] | ascii::no_case["EXP"]
                        | ascii::no_case["DISTANCE"]
                        | ascii::no_case["DEGREES"] | ascii::no_case["COS"]
                        | ascii::no_case["COORDSYS"] | ascii::no_case["COORD2"]
                        | ascii::no_case["COORD1"] | ascii::no_case["CONTAINS"]
                        | ascii::no_case["CIRCLE"] | ascii::no_case["CENTROID"]
                        | ascii::no_case["CEILING"] | ascii::no_case["BOX"]
                        | ascii::no_case["ATAN2"] | ascii::no_case["ATAN"]
                        | ascii::no_case["ASIN"] | ascii::no_case["AREA"]
                        | ascii::no_case["ACOS"] | ascii::no_case["ABS"];

  /// Split up SQL_reserved_word to help memory usage and compile times.
  SQL_reserved_word_00 %= ascii::no_case["ZONE"] | ascii::no_case["YEAR"]
                          | ascii::no_case["WRITE"] | ascii::no_case["WORK"]
                          | ascii::no_case["WITH"] | ascii::no_case["WHERE"]
                          | ascii::no_case["WHENEVER"] | ascii::no_case["WHEN"]
                          | ascii::no_case["VIEW"] | ascii::no_case["VARYING"]
                          | ascii::no_case["VARCHAR"]
                          | ascii::no_case["VALUES"] | ascii::no_case["VALUE"]
                          | ascii::no_case["USING"] | ascii::no_case["USER"]
                          | ascii::no_case["USAGE"];

  SQL_reserved_word_01
      %= ascii::no_case["UPPER"] | ascii::no_case["UPDATE"]
         | ascii::no_case["UNKNOWN"] | ascii::no_case["UNIQUE"]
         | ascii::no_case["UNION"] | ascii::no_case["TRUE"]
         | ascii::no_case["TRIM"] | ascii::no_case["TRANSLATION"]
         | ascii::no_case["TRANSLATE"] | ascii::no_case["TRANSACTION"]
         | ascii::no_case["TRAILING"] | ascii::no_case["TO"]
         | ascii::no_case["TIMEZONE_MINUTE"] | ascii::no_case["TIMEZONE_HOUR"]
         | ascii::no_case["TIMESTAMP"];

  SQL_reserved_word_02
      %= ascii::no_case["TIME"] | ascii::no_case["THEN"]
         | ascii::no_case["TEMPORARY"] | ascii::no_case["TABLE"]
         | ascii::no_case["SYSTEM_USER"] | ascii::no_case["SUM"]
         | ascii::no_case["SUBSTRING"] | ascii::no_case["SQLSTATE"]
         | ascii::no_case["SQLERROR"] | ascii::no_case["SQLCODE"]
         | ascii::no_case["SQL"] | ascii::no_case["SPACE"]
         | ascii::no_case["SOME"] | ascii::no_case["SMALLINT"]
         | ascii::no_case["SIZE"] | ascii::no_case["SET"];

  SQL_reserved_word_03
      %= ascii::no_case["SESSION_USER"] | ascii::no_case["SESSION"]
         | ascii::no_case["SELECT"] | ascii::no_case["SECTION"]
         | ascii::no_case["SECOND"] | ascii::no_case["SCROLL"]
         | ascii::no_case["SCHEMA"] | ascii::no_case["ROWS"]
         | ascii::no_case["ROLLBACK"] | ascii::no_case["RIGHT"]
         | ascii::no_case["REVOKE"] | ascii::no_case["RESTRICT"]
         | ascii::no_case["RELATIVE"] | ascii::no_case["REFERENCES"]
         | ascii::no_case["REAL"] | ascii::no_case["READ"];

  SQL_reserved_word_10
      %= ascii::no_case["PUBLIC"] | ascii::no_case["PROCEDURE"]
         | ascii::no_case["PRIVILEGES"] | ascii::no_case["PRIOR"]
         | ascii::no_case["PRIMARY"] | ascii::no_case["PRESERVE"]
         | ascii::no_case["PREPARE"] | ascii::no_case["PRECISION"]
         | ascii::no_case["POSITION"] | ascii::no_case["PARTIAL"]
         | ascii::no_case["PAD"] | ascii::no_case["OVERLAPS"]
         | ascii::no_case["OUTPUT"] | ascii::no_case["OUTER"]
         | ascii::no_case["ORDER"] | ascii::no_case["OR"];

  SQL_reserved_word_11
      %= ascii::no_case["OPTION"] | ascii::no_case["OPEN"]
         | ascii::no_case["ONLY"] | ascii::no_case["ON"] | ascii::no_case["OF"]
         | ascii::no_case["OCTET_LENGTH"] | ascii::no_case["NUMERIC"]
         | ascii::no_case["NULLIF"] | ascii::no_case["NULL"]
         | ascii::no_case["NOT"] | ascii::no_case["NO"]
         | ascii::no_case["NEXT"] | ascii::no_case["NCHAR"]
         | ascii::no_case["NATURAL"] | ascii::no_case["NATIONAL"];

  SQL_reserved_word_12 %= ascii::no_case["NAMES"] | ascii::no_case["MONTH"]
                          | ascii::no_case["MODULE"] | ascii::no_case["MINUTE"]
                          | ascii::no_case["MIN"] | ascii::no_case["MAX"]
                          | ascii::no_case["MATCH"] | ascii::no_case["LOWER"]
                          | ascii::no_case["LOCAL"] | ascii::no_case["LIKE"]
                          | ascii::no_case["LEVEL"] | ascii::no_case["LEFT"]
                          | ascii::no_case["LEADING"] | ascii::no_case["LAST"]
                          | ascii::no_case["LANGUAGE"] | ascii::no_case["KEY"];

  SQL_reserved_word_13
      %= ascii::no_case["JOIN"] | ascii::no_case["ISOLATION"]
         | ascii::no_case["IS"] | ascii::no_case["INTO"]
         | ascii::no_case["INTERVAL"] | ascii::no_case["INTERSECT"]
         | ascii::no_case["INTEGER"] | ascii::no_case["INT"]
         | ascii::no_case["INSERT"] | ascii::no_case["INSENSITIVE"]
         | ascii::no_case["INPUT"] | ascii::no_case["INNER"]
         | ascii::no_case["INITIALLY"] | ascii::no_case["INDICATOR"]
         | ascii::no_case["IN"] | ascii::no_case["IMMEDIATE"];

  SQL_reserved_word_20 %= ascii::no_case["IDENTITY"] | ascii::no_case["HOUR"]
                          | ascii::no_case["HAVING"] | ascii::no_case["GROUP"]
                          | ascii::no_case["GRANT"] | ascii::no_case["GOTO"]
                          | ascii::no_case["GO"] | ascii::no_case["GLOBAL"]
                          | ascii::no_case["GET"] | ascii::no_case["FULL"]
                          | ascii::no_case["FROM"] | ascii::no_case["FOUND"]
                          | ascii::no_case["FOREIGN"] | ascii::no_case["FOR"]
                          | ascii::no_case["FLOAT"] | ascii::no_case["FIRST"];

  SQL_reserved_word_21
      %= ascii::no_case["FETCH"] | ascii::no_case["FALSE"]
         | ascii::no_case["EXTRACT"] | ascii::no_case["EXTERNAL"]
         | ascii::no_case["EXISTS"] | ascii::no_case["EXECUTE"]
         | ascii::no_case["EXEC"] | ascii::no_case["EXCEPTION"]
         | ascii::no_case["EXCEPT"] | ascii::no_case["ESCAPE"]
         | ascii::no_case["END-EXEC"] | ascii::no_case["END"]
         | ascii::no_case["ELSE"] | ascii::no_case["DROP"]
         | ascii::no_case["DOUBLE"] | ascii::no_case["DOMAIN"];

  SQL_reserved_word_22
      %= ascii::no_case["DISTINCT"] | ascii::no_case["DISCONNECT"]
         | ascii::no_case["DIAGNOSTICS"] | ascii::no_case["DESCRIPTOR"]
         | ascii::no_case["DESCRIBE"] | ascii::no_case["DESC"]
         | ascii::no_case["DELETE"] | ascii::no_case["DEFERRED"]
         | ascii::no_case["DEFERRABLE"] | ascii::no_case["DEFAULT"]
         | ascii::no_case["DECLARE"] | ascii::no_case["DECIMAL"]
         | ascii::no_case["DEALLOCATE"] | ascii::no_case["DAY"]
         | ascii::no_case["DATE"] | ascii::no_case["CURSOR"];

  SQL_reserved_word_23
      %= ascii::no_case["CURRENT_USER"] | ascii::no_case["CURRENT_TIMESTAMP"]
         | ascii::no_case["CURRENT_TIME"] | ascii::no_case["CURRENT_DATE"]
         | ascii::no_case["CURRENT"] | ascii::no_case["CROSS"]
         | ascii::no_case["CREATE"] | ascii::no_case["COUNT"]
         | ascii::no_case["CORRESPONDING"] | ascii::no_case["CONVERT"]
         | ascii::no_case["CONTINUE"] | ascii::no_case["CONSTRAINTS"]
         | ascii::no_case["CONSTRAINT"] | ascii::no_case["CONNECTION"]
         | ascii::no_case["CONNECT"] | ascii::no_case["COMMIT"];

  SQL_reserved_word_30
      %= ascii::no_case["COLUMN"] | ascii::no_case["COLLATION"]
         | ascii::no_case["COLLATE"] | ascii::no_case["COALESCE"]
         | ascii::no_case["CLOSE"] | ascii::no_case["CHECK"]
         | ascii::no_case["CHAR_LENGTH"] | ascii::no_case["CHARACTER_LENGTH"]
         | ascii::no_case["CHARACTER"] | ascii::no_case["CHAR"]
         | ascii::no_case["CATALOG"] | ascii::no_case["CAST"]
         | ascii::no_case["CASE"] | ascii::no_case["CASCADED"]
         | ascii::no_case["CASCADE"] | ascii::no_case["BY"];

  SQL_reserved_word_31 %= ascii::no_case["BOTH"] | ascii::no_case["BIT_LENGTH"]
                          | ascii::no_case["BIT"] | ascii::no_case["BETWEEN"]
                          | ascii::no_case["BEGIN"] | ascii::no_case["AVG"]
                          | ascii::no_case["AUTHORIZATION"]
                          | ascii::no_case["AT"] | ascii::no_case["ASSERTION"]
                          | ascii::no_case["ASC"] | ascii::no_case["AS"]
                          | ascii::no_case["ARE"] | ascii::no_case["ANY"]
                          | ascii::no_case["AND"] | ascii::no_case["ALTER"]
                          | ascii::no_case["ALLOCATE"];

  SQL_reserved_word_32 %= ascii::no_case["ALL"] | ascii::no_case["ADD"]
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
}
