#include "../Query.hxx"
#include "ADQL_parser.hxx"

ADQL::Query::Query(
        const std::string &input,
        const std::map<std::string, std::string> &table_mapping_for_columns) {
    ADQL_parser parser(table_mapping_for_columns);
    std::string::const_iterator begin(input.begin()), end(input.end());

    bool valid(phrase_parse(begin, end, parser, boost::spirit::ascii::space,
                            query_specification));

    if (!valid) {
        auto error = parser.error_stream.str();
        if (error.empty()) error = "Error: Expecting <SELECT> here: \"" + input + "\"";
        ;
        throw std::runtime_error(error);
    } else if (begin != end) {
        throw std::runtime_error("Error: Unexpected terms at the end: " +
                                 std::string(begin, end));
    }
}
