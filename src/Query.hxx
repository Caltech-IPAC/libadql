#ifndef ADQL_QUERY_HXX
#define ADQL_QUERY_HXX

#include <vector>
#include <string>
#include "Geometry.hxx"

namespace ADQL
{
class Query
{
public:
  std::vector<std::string> output_columns;
  std::string table;
  Geometry geometry;

  Query (const std::string &input);
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Query,
                           (std::vector<std::string>,
                            output_columns)(std::string, table)(ADQL::Geometry,
                                                                geometry))

#endif
