#pragma once

#include "Factor/Numeric_Primary.hxx"

namespace ADQL
{
class Factor
{
public:
  std::string sign;
  Numeric_Primary numeric_primary;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Factor &factor)
{
  return os << factor.sign << factor.numeric_primary;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Factor,
                           (std::string, sign)(ADQL::Numeric_Primary,
                                               numeric_primary))
