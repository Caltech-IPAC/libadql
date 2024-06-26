#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Query/Query_Specification.hxx"
#include "to_string.hxx"

namespace ADQL {
class Query {
public:
    Query_Specification query_specification;

    Query(const std::string &input,
          const std::map<std::string, std::string> &table_mapping_for_columns);
    Query(const std::string &input) : Query(input, {{}}) {}
    Query() = default;
    Query(const Query &) = default;

    std::vector<std::pair<std::string, std::string> > simplified_columns(
            uint idx = 0) const;
    std::vector<std::vector<std::pair<std::string, std::string> > >
    simplified_columns_list() const;

    // Called from query_server's planck-support code, this function
    // allows for a (single) spatial/geometric constraint.
    bool simple_spatial_query() const {
        return (query_specification.get_num_union_components() == 1 &&
                (query_specification.get_initial_sfw().select.all_or_distinct.empty() ||
                 query_specification.get_initial_sfw().select.all_or_distinct ==
                         "ALL") &&
                query_specification.get_initial_sfw().where.search_condition.empty() &&
                query_specification.with.empty() &&
                query_specification.group_by.empty() &&
                query_specification.order_by.empty() &&
                query_specification.having.empty());
    }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Query &query) {
    return os << query.query_specification;
}
}  // namespace ADQL
