#pragma once

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include "Query/Query_Specification.hxx"
#include "to_string.hxx"

namespace ADQL
{
class Query
{
public:
  Query_Specification query_specification;

  Query (const std::string &input,
         const std::map<std::string,std::string> &table_mapping);
  Query (const std::string &input): Query(input,{{}}) {}

  std::vector<std::pair<std::string,std::string> > simplified_columns() const;

  bool simple_query() const
  {
    return (query_specification.all_or_distinct.empty()
            || query_specification.all_or_distinct=="ALL")
      && query_specification.where.search_condition.empty()
      && query_specification.group_by.empty()
      && query_specification.order_by.empty()
      && query_specification.having.empty();
  }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Query &query)
{
  return os << query.query_specification;
}
}
