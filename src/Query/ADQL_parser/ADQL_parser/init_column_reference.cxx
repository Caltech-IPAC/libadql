#include <boost/spirit/include/phoenix_bind.hpp>

#include "../../ADQL_parser.hxx"

namespace {
std::string checked_mapping(const std::map<std::string, std::string> &mapping,
                            const std::string &s) {
    auto i = mapping.find(s);
    if (i == mapping.end())
        throw std::runtime_error("Error: The table TAP_UPLOAD." + s +
                                 " was not found.  Is it misspelled?");
    return i->second;
}
}  // namespace

void ADQL_parser::init_column_reference() {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::alnum;
    using boost::spirit::qi::alpha;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::hold;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::labels::_val;
    using boost::spirit::qi::lexeme;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::lower;
    using boost::spirit::qi::no_skip;
    using boost::spirit::qi::omit;
    using boost::spirit::qi::print;
    using boost::spirit::qi::ulong_long;
    namespace ascii = boost::spirit::ascii;

    period %= char_('.');

    unqualified_schema_name %= identifier;

    /// The spec says to have correlation_name as an alternate, but
    /// table_name matches everything that correlation name matches,
    /// so correlation_name will never match.
    qualifier %= table_name;

    /// We have to put the tap_upload_identifier into its own rule
    /// instead of folding it in with tap_upload, because otherwise it
    /// starts matching the whole string column expression instead of
    /// just this column reference.
    ///
    /// We use += because _val already has the results of the entire
    /// parsed column expression, not just the identifier.  This is a
    /// very confusing part of boost::spirit.
    tap_upload_identifier =
            identifier[_val += boost::phoenix::bind(&checked_mapping, table_mapping,
                                                    boost::spirit::qi::labels::_1)];
    tap_upload_identifier.name("TAP_UPLOAD identifier");

    tap_upload %= "TAP_UPLOAD." > tap_upload_identifier;
    tap_upload.name("TAP_UPLOAD");

    /// I have to manually expand the possibilities in
    /// column_reference and table name, because a catalog.schema can
    /// match against schema.table or table.column, gobbling up the
    /// table or column name and making the parse fail.
    table_name %= tap_upload |
                  hold[catalog_name >> period >> unqualified_schema_name >> period >>
                       identifier] |
                  hold[unqualified_schema_name >> period >> identifier] | identifier;
    table_name.name("table name");

    catalog_name %= identifier;
    catalog_name.name("catalog name");

    catalog_schema_qualifier_column %=
            identifier >> '.' >> identifier >> '.' >> identifier >> '.' >> identifier;
    catalog_schema_qualifier_column.name("catalog schema qualifier column");
    schema_qualifier_column %= identifier >> '.' >> identifier >> '.' >> identifier;
    schema_qualifier_column.name("schema qualifier column");
    qualifier_column %= (tap_upload | identifier) >> '.' >> identifier;
    qualifier_column.name("qualifier column");
    column_reference %= catalog_schema_qualifier_column | schema_qualifier_column |
                        qualifier_column | identifier;
    column_reference.name("column reference");

#ifdef DEBUG_COL
    BOOST_SPIRIT_DEBUG_NODE(tap_upload_identifier);
    BOOST_SPIRIT_DEBUG_NODE(tap_upload);
    BOOST_SPIRIT_DEBUG_NODE(table_name);
    BOOST_SPIRIT_DEBUG_NODE(catalog_name);
    BOOST_SPIRIT_DEBUG_NODE(catalog_schema_qualifier_column);
    BOOST_SPIRIT_DEBUG_NODE(schema_qualifier_column);
    BOOST_SPIRIT_DEBUG_NODE(qualifier_column);
    BOOST_SPIRIT_DEBUG_NODE(column_reference);
#endif
}
