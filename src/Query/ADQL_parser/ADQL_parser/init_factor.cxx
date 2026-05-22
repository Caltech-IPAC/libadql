#include "../../ADQL_parser.hxx"

void ADQL_parser::init_factor() {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::alnum;
    using boost::spirit::qi::alpha;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::hold;
    using boost::spirit::qi::lexeme;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::lower;
    using boost::spirit::qi::no_skip;
    using boost::spirit::qi::omit;
    using boost::spirit::qi::print;
    using boost::spirit::qi::ulong_long;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::labels::_val;
    namespace ascii = boost::spirit::ascii;

    set_function_type %= ascii::no_case[ascii::string("AVG")] |
                         ascii::no_case[ascii::string("MAX")] |
                         ascii::no_case[ascii::string("MIN")] |
                         ascii::no_case[ascii::string("SUM")] |
                         ascii::no_case[ascii::string("COUNT")];
    set_function_type.name("set_function_type");

    // This is a little funky because we need to preserve the space
    // between the set_quantifier and whatever follows it.
    set_quantifier %= hold[lexeme[(ascii::no_case[ascii::string("DISTINCT")] |
                                   ascii::no_case[ascii::string("ALL")]) >>
                                  &boost::spirit::qi::space]];
    set_quantifier.name("set_quantifier");

    general_set_args = -set_quantifier >> value_expression;
    general_set_function %= set_function_type >> '(' > general_set_args > ')';
    general_set_function.name("general_set_function");

    count_star %= ascii::no_case[ascii::string("COUNT")] >> char_('(') >> char_('*') >
                  char_(')');
    set_function_specification %= count_star | general_set_function;
    set_function_specification.name("set_function_specification");

    null_literal %= ascii::no_case[ascii::string("NULL")];

    result %= value_expression | null_literal;
    result.name("result");

    simple_when %= ascii::no_case["WHEN"] >> &no_skip[boost::spirit::qi::space] >
                   value_expression >> ascii::no_case["THEN"] >
                   &no_skip[boost::spirit::qi::space] > result;
    simple_when.name("simple_when");

    simple_whens %= +simple_when;
    simple_whens.name("simple_whens");

    else_clause %=
            ascii::no_case["ELSE"] >> &no_skip[boost::spirit::qi::space] >> result;
    else_clause.name("else_clause");

    // boost::spirit gets wonky if I try to use the '>' operator for
    // simple_whens
    simple_case %=
            value_expression >> simple_whens >> -else_clause > ascii::no_case["END"];
    simple_case.name("simple_case");

    searched_when %= ascii::no_case["WHEN"] >> &no_skip[boost::spirit::qi::space] >>
                     search_condition >> ascii::no_case["THEN"] >>
                     &no_skip[boost::spirit::qi::space] >> result;
    searched_when.name("searched_when");

    searched_whens %= +searched_when;
    searched_whens.name("searched_whens");

    searched_case %= searched_whens >> -else_clause >>
                     &no_skip[boost::spirit::qi::space] >> ascii::no_case["END"];
    searched_case.name("searched_case");

    case_specification %= ascii::no_case["CASE"] >> &no_skip[boost::spirit::qi::space] >
                          (simple_case | searched_case);
    case_specification.name("case_specification");

    nullif %= ascii::no_case["NULLIF"] >> '(' >> value_expression >> ',' >>
              value_expression >> ')';
    nullif.name("nullif");

    coalesce %= ascii::no_case["COALESCE"] >> '(' >> (value_expression % ',') >> ')';
    coalesce.name("coalesce");

    case_abbreviation %= nullif | coalesce;
    case_abbreviation.name("case_abbreviation");

    case_expression %= case_abbreviation | case_specification;
    case_expression.name("case_expression");

    any_expression %= ascii::no_case["ANY"] >> '(' > value_expression > ')';
    any_expression.name("any_expression");

    // The BNF for SQL 99 uses an array_element_reference intermediate
    // rule.  However, that rule first checks for value_expression, so
    // you get an infinite recursion because it keeps matching the
    // value_expression part of the array element.  So instead we
    // implement array elements as optional decorators after an expression.

    value_subexpression %= hold['(' >> value_expression >> ')'];
    value_subexpression.name("value_subexpression");

    array_index %= hold['[' >> value_expression >> ']'];
    array_index.name("array_index");

    null_cast %= ascii::no_case[ascii::string("NULL::char")] |
                 ascii::no_case[ascii::string("NULL::int")] |
                 ascii::no_case[ascii::string("NULL::float")];
    null_cast.name("null_cast");

    value_expression_primary %=
            (array_constructor | unsigned_value_specification | column_reference |
             set_function_specification | case_expression | any_expression | null_cast |
             null_literal | value_subexpression) >>
            *array_index;
    value_expression_primary.name("value_expression_primary");

    // Custom array_expression so that SQL 99 array literals can pass
    // through
    array_constructor %=
            ascii::no_case["ARRAY"] >> '[' >> (value_expression % ',') > ']';
    array_constructor.name("array_constructor");

    // Reverse-sorted within groups as in init_reserved_word() to
    // prevent early matches. Could be reverse-sorted in one big group
    // if necessary.

    // Note: Despite their potential for misuse in blind injection
    // attacks, the functions SUBSTR, SUBSTRING, and INSTR are
    // whitelisted because they have legitimate uses in TAP
    // queries. The functions ASCII() and CHR(), though, are omitted
    // from the whitelist as of 22May26.

    whitelisted_function_name %=
            // IRSA UDFs
            ascii::no_case[ascii::string("STRIP_URL_PREFIX")] |
            ascii::no_case[ascii::string("SIA2_CLOUD_ACCESS_COLUMN")] |
            ascii::no_case[ascii::string("SIA1_CLOUD_ACCESS_COLUMN")] |
            ascii::no_case[ascii::string("RA_TO_SEXAGESIMAL")] |
            ascii::no_case[ascii::string("PT_TO_REGION")] |
            ascii::no_case[ascii::string("POSITION_ANGLE")] |
            ascii::no_case[ascii::string("POLY_TO_REGION")] |
            ascii::no_case[ascii::string("POLY_TO_RA")] |
            ascii::no_case[ascii::string("POLY_TO_DEC")] |
            ascii::no_case[ascii::string("GET_MOCS")] |
            ascii::no_case[ascii::string("GET_CONTENTTYPE_SORT_SURROGATE")] |
            ascii::no_case[ascii::string("EXTRACT_URL_BASENAME")] |
            ascii::no_case[ascii::string("DEC_TO_SEXAGESIMAL")] |

            // PostgreSQL/SQL functions
            ascii::no_case[ascii::string("TYPEOF")] |
            ascii::no_case[ascii::string("TO_TIMESTAMP")] |
            ascii::no_case[ascii::string("TO_NUMBER")] |
            ascii::no_case[ascii::string("TO_DATE")] |
            ascii::no_case[ascii::string("TO_CHAR")] |
            ascii::no_case[ascii::string("TIMEZONE")] |
            ascii::no_case[ascii::string("SYSDATE")] |
            ascii::no_case[ascii::string("SUBSTRING")] |
            ascii::no_case[ascii::string("SUBSTR")] |
            ascii::no_case[ascii::string("STRPOS")] |
            ascii::no_case[ascii::string("STRING_AGG")] |
            ascii::no_case[ascii::string("STDDEV")] |
            ascii::no_case[ascii::string("SPLIT_PART")] |
            ascii::no_case[ascii::string("REPLACE")] |
            ascii::no_case[ascii::string("RANDOM")] |
            ascii::no_case[ascii::string("NOW")] |
            ascii::no_case[ascii::string("MEDIAN")] |
            ascii::no_case[ascii::string("MD5")] | ascii::no_case[ascii::string("LN")] |
            ascii::no_case[ascii::string("LENGTH")] |
            ascii::no_case[ascii::string("LEAST")] |
            ascii::no_case[ascii::string("JSONB_EXTRACT_PATH_TEXT")] |
            ascii::no_case[ascii::string("JSON_EXTRACT_PATH_TEXT")] |
            ascii::no_case[ascii::string("INSTR")] |
            ascii::no_case[ascii::string("GREATEST")] |
            ascii::no_case[ascii::string("GETDATE")] |
            ascii::no_case[ascii::string("FORMAT")] |
            ascii::no_case[ascii::string("FLOOR")] |
            ascii::no_case[ascii::string("CONCAT")] |
            ascii::no_case[ascii::string("CLOCK_TIMESTAMP")] |
            ascii::no_case[ascii::string("CHAR_LENGTH")] |
            ascii::no_case[ascii::string("CEILING")] |
            ascii::no_case[ascii::string("CEIL")] |

            // PostGIS type constructors
            ascii::no_case[ascii::string("GEOMETRY")] |
            ascii::no_case[ascii::string("GEOGRAPHY")] |

            // ADQL reserved words that are also valid function names
            ascii::no_case[ascii::string("SQRT")] |
            ascii::no_case[ascii::string("ROUND")] |
            ascii::no_case[ascii::string("POWER")] |
            ascii::no_case[ascii::string("MOD")] |
            ascii::no_case[ascii::string("LOG10")] |
            ascii::no_case[ascii::string("LOG")] |
            ascii::no_case[ascii::string("EXP")] |
            ascii::no_case[ascii::string("COORD2")] |
            ascii::no_case[ascii::string("COORD1")] |
            ascii::no_case[ascii::string("ABS")] |

            // SQL reserved words that are also valid function names
            ascii::no_case[ascii::string("UPPER")] |
            ascii::no_case[ascii::string("TRIM")] |
            ascii::no_case[ascii::string("SUM")] |
            ascii::no_case[ascii::string("ROW_NUMBER")] |
            ascii::no_case[ascii::string("RIGHT")] |
            ascii::no_case[ascii::string("LOWER")] |
            ascii::no_case[ascii::string("LEFT")] |
            ascii::no_case[ascii::string("DISTINCT")] |
            ascii::no_case[ascii::string("CAST")] |

            // ST_ prefix — PostGIS functions
            (ascii::no_case[ascii::string("ST_")] >> all_identifiers) |

            // ivo_ prefix — IVOA functions
            (ascii::no_case[ascii::string("ivo_")] >> all_identifiers) |

            // q3c_ prefix — Q3C spatial indexing functions
            (ascii::no_case[ascii::string("q3c_")] >> all_identifiers);

    whitelisted_function_name.name("whitelisted_function_name");

    whitelisted_function_param %= value_expression;
    whitelisted_function_param.name("whitelisted_function_param");

    whitelisted_function %= hold[whitelisted_function_name >> '('] >>
                            -(whitelisted_function_param % ',') >> ')';

    whitelisted_function.name("whitelisted_function");

    sql_no_arg_function %= ascii::no_case[ascii::string("CURRENT_TIMESTAMP")];

    cast_as %= ascii::no_case[ascii::string("NUMERIC")] |
               ascii::no_case[ascii::string("FLOAT4")] |
               ascii::no_case[ascii::string("INTEGER")] |
               ascii::no_case[ascii::string("BIGINT")] |
               ascii::no_case[ascii::string("FLOAT8")] |
               ascii::no_case[ascii::string("VARCHAR2")] |
               ascii::no_case[ascii::string("VARCHAR")] |
               ascii::no_case[ascii::string("CHAR")] |
               ascii::no_case[ascii::string("TEXT")] |
               ascii::no_case[ascii::string("public.GEOGRAPHY")] |
               ascii::no_case[ascii::string("public.GEOMETRY")];

    cast_function %= hold[ascii::no_case["CAST"] >> '(' >> value_expression >>
                          &no_skip[boost::spirit::qi::space] >> ascii::no_case["AS"] >>
                          &no_skip[boost::spirit::qi::space] >> cast_as >>
                          -('(' > unsigned_integer > ')') >> ')'];
    cast_function.name("cast_function");

    position_function %=
            hold[ascii::no_case["POSITION"] >> '(' >> character_string_literal >>
                 &no_skip[boost::spirit::qi::space] >> ascii::no_case["IN"] >>
                 &no_skip[boost::spirit::qi::space] >> column_reference >> ')'];
    position_function.name("position_function");

    // FIXME: numeric_value_function should have
    // numeric_geometry_function
    numeric_value_function %= trig_function | math_function | cast_function |
                              position_function | non_predicate_geometry_function |
                              whitelisted_function | sql_no_arg_function;

    numeric_value_function.name("numeric_value_function");
    // Flipped the order here, because a value_expression can match a
    // function name.
    numeric_primary %= numeric_value_function | value_expression_primary;
    numeric_primary.name("numeric_primary");

    factor %= -sign >> numeric_primary;
    factor.name("factor");

#ifdef DEBUG_FAC
    BOOST_SPIRIT_DEBUG_NODE(set_function_type);
    BOOST_SPIRIT_DEBUG_NODE(set_quantifier);
    BOOST_SPIRIT_DEBUG_NODE(general_set_function);
    BOOST_SPIRIT_DEBUG_NODE(set_function_specification);
    BOOST_SPIRIT_DEBUG_NODE(result);
    BOOST_SPIRIT_DEBUG_NODE(simple_when);
    BOOST_SPIRIT_DEBUG_NODE(simple_whens);
    BOOST_SPIRIT_DEBUG_NODE(else_clause);
    BOOST_SPIRIT_DEBUG_NODE(simple_case);
    BOOST_SPIRIT_DEBUG_NODE(searched_when);
    BOOST_SPIRIT_DEBUG_NODE(searched_whens);
    BOOST_SPIRIT_DEBUG_NODE(searched_case);
    BOOST_SPIRIT_DEBUG_NODE(case_specification);
    BOOST_SPIRIT_DEBUG_NODE(nullif);
    BOOST_SPIRIT_DEBUG_NODE(coalesce);
    BOOST_SPIRIT_DEBUG_NODE(case_abbreviation);
    BOOST_SPIRIT_DEBUG_NODE(case_expression);
    BOOST_SPIRIT_DEBUG_NODE(any_expression);
    BOOST_SPIRIT_DEBUG_NODE(value_subexpression);
    BOOST_SPIRIT_DEBUG_NODE(array_index);
    BOOST_SPIRIT_DEBUG_NODE(null_cast);
    BOOST_SPIRIT_DEBUG_NODE(value_expression_primary);
    BOOST_SPIRIT_DEBUG_NODE(array_constructor);
    BOOST_SPIRIT_DEBUG_NODE(whitelisted_function_name);
    BOOST_SPIRIT_DEBUG_NODE(whitelisted_function_param);
    BOOST_SPIRIT_DEBUG_NODE(whitelisted_function);
    BOOST_SPIRIT_DEBUG_NODE(cast_function);
    BOOST_SPIRIT_DEBUG_NODE(position_function);
    BOOST_SPIRIT_DEBUG_NODE(numeric_value_function);
    BOOST_SPIRIT_DEBUG_NODE(numeric_primary);
    BOOST_SPIRIT_DEBUG_NODE(factor);
#endif
}
