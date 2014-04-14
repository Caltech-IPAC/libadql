#pragma once

#include "../../../../Number_Variant.hxx"
namespace ADQL
{
class Between_Predicate
{
public:
  Number_Variant value, low, high;
  std::string Not;
};
}

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Between_Predicate &b)
{
  return os << b.value << " " << b.Not << (b.Not.empty() ? "" : " ")
            << "BETWEEN " << b.low << " AND " << b.high;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Between_Predicate,
                           (ADQL::Number_Variant, value)
                           (std::string, Not)
                           (ADQL::Number_Variant, low)
                           (ADQL::Number_Variant, high))

