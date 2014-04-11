#pragma once

#include <boost/fusion/include/io.hpp>
#include <vector>
#include <string>
#include "Query/Geometry.hxx"
#include "Query/As.hxx"
#include "Query/Search_Condition.hxx"

namespace ADQL
{
typedef boost::variant<As, std::string> column_variant;

class Query
{
public:
  std::vector<column_variant> output_columns;
  std::string table;
  Geometry geometry;
  Comparison_Predicate comparison_predicate;
  Search_Condition search_condition;

  Query (const std::string &input);
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Query,
                           (std::vector<ADQL::column_variant>,output_columns)
                           (std::string, table)
                           (ADQL::Geometry,geometry)
                           (ADQL::Comparison_Predicate,comparison_predicate)
                           )

