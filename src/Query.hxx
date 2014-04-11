#pragma once

#include <vector>
#include <string>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"
#include "Query/As.hxx"
#include "Query/Where.hxx"

namespace ADQL
{
typedef boost::variant<As, std::string> column_variant;

class Query
{
public:
  std::vector<column_variant> output_columns;
  std::string table;
  Where where;

  Query (const std::string &input);
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Query,
                           (std::vector<ADQL::column_variant>,output_columns)
                           (std::string, table)
                           (ADQL::Where, where)
                           )

