#pragma once

#include "Value_Expression.hxx"

namespace ADQL
{
class As
{
public:
  Value_Expression expression;
  std::string as;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::As &as)
{
  return os << as.expression << " AS " << as.as;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::As, (ADQL::Value_Expression,
                                      expression)(std::string, as))
