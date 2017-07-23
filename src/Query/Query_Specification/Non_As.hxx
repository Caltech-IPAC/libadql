#pragma once

#include "Value_Expression.hxx"

namespace ADQL
{
class Non_As
{
public:
  std::string non_as;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Non_As &non_as)
{
  return os << non_as.non_as;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Non_As, (std::string, non_as))
