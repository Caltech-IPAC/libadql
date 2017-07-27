#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Sort_Specification
{
public:
  std::string key, ordering;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Sort_Specification &sort_specification)
{
  os << sort_specification.key;
  if (!sort_specification.ordering.empty())
    {
      os << " " << sort_specification.ordering;
    }
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Sort_Specification,
                           (std::string, key)(std::string, ordering))
