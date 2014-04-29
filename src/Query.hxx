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
  std::string all_or_distinct;
  std::string table;
  Where where;

  Query (const std::string &input);

  std::string output_columns_string() const
  {
    std::stringstream ss;
    for(auto &o: output_columns)
      {
        ss << o << ", ";
      }        
    std::string result=ss.str();
    /// Trim off the trailing comma
    result=result.substr(0,result.size()-2);
    return result;
  }
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Query,
                           (std::string, all_or_distinct)
                           (std::vector<ADQL::column_variant>,output_columns)
                           (std::string, table)
                           (ADQL::Where, where)
                           )

