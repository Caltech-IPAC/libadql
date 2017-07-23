#pragma once

#include "Value_Expression.hxx"

namespace ADQL
{
class Non_As
{
public:
  typedef boost::variant<std::string, Value_Expression> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Non_As &non_as)
{
  return os << non_as.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Non_As, (ADQL::Non_As::Variant, variant))
