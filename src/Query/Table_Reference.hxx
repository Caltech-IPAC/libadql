#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ADQL
{
class Table_Reference
{
public:
  std::string name, as;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Table_Reference &table)
{
  os << table.name;
  if (!table.as.empty ())
    os << " AS " << table.as;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Table_Reference,
                           (std::string, name)(std::string, as))
