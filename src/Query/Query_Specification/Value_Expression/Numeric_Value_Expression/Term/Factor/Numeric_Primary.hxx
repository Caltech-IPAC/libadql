#pragma once

#include "Numeric_Primary/Numeric_Value_Function.hxx"

namespace ADQL
{
class Numeric_Primary
{
public:
  std::string numeric;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Numeric_Primary &numeric_primary)
{
  return os << numeric_primary.numeric;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Primary,
                           (std::string, numeric))
