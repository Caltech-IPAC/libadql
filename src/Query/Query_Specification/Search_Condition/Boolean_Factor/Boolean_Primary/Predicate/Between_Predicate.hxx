#pragma once

#include "../../../../Value_Expression.hxx"

namespace ADQL
{
class Between_Predicate
{
public:
  Value_Expression value, low, high;
  std::string Not;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Between_Predicate &b)
{
  return os << b.value << " " << b.Not << (b.Not.empty () ? "" : " ")
            << "BETWEEN " << b.low << " AND " << b.high;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Between_Predicate,
                           (ADQL::Value_Expression,
                            value)(std::string,
                                   Not)(ADQL::Value_Expression,
                                        low)(ADQL::Value_Expression, high))
