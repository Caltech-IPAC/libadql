#include "../../ADQL_parser.hxx"

void ADQL_parser::init_column_reference()
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

  period %= char_ ('.');

  catalog_name %= identifier;
  unqualified_schema_name %= identifier;

  correlation_name %= identifier;
  correlation_specification %= -lexeme[ascii::no_case[ascii::string ("AS")]
                                       > &boost::spirit::qi::space]
    >> correlation_name;

  /// The spec says to have correlation_name as an alternate, but
  /// table_name matches everything that correlation name matches,
  /// so correlation_name will never match.
  qualifier %= table_name;

  tap_upload
    %= "TAP_UPLOAD."
    // > identifier[_val=mapit];
    // > identifier[write_tap_upload];
    > identifier[_val = boost::phoenix::ref (table_mapping)[_1]];
  // > identifier[_val = boost::phoenix::at (table_mapping,_1)];
  // > identifier[tap_upload_matcher(table_mapping)];
  // > identifier[boost::bind(&tap_upload_matcher::check,tap_upload_matcher(table_mapping),_val,_1)];
  // > identifier[boost::bind (&std::map<std::string,std::string>::at,&table_mapping,_1)];
  tap_upload.name ("TAP_UPLOAD");

  // boost::spirit::qi::on_error<boost::spirit::qi::fail>
  //   (
  //    tap_upload
  //    , boost::phoenix::ref( (std::ostream&)error_stream)
  //    << boost::phoenix::val("Error! Expecting ")
  //    << boost::spirit::qi::labels::_4
  //    << boost::phoenix::val(" here: \"")
  //    << boost::phoenix::construct<std::string>(_3, _2)
  //    << boost::phoenix::val("\"")
  //    << std::endl
  //    );

  /// I have to manually expand the possibilities in
  /// column_reference and table name, because a catalog.schema can
  /// match against schema.table or table.column, gobbling up the
  /// table or column name and making the parse fail.
  table_name %= tap_upload
    | hold[catalog_name >> period >> unqualified_schema_name
           >> period >> identifier]
    | hold[unqualified_schema_name >> period >> identifier]
    | identifier;
  table_name.name ("table name");

  column_reference
    %= hold[tap_upload >> period >> identifier]
    | hold[catalog_name >> period >> unqualified_schema_name >> period
           >> identifier >> period >> identifier]
    | hold[unqualified_schema_name >> period >> identifier >> period
           >> identifier] | hold[identifier >> period >> identifier]
    | identifier;
}
