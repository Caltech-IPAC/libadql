#pragma once

namespace ADQL
{
class Between_Predicate
{
public:
  std::string value, low, high;
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
                           (std::string, value)(std::string,
                                                Not)(std::string,
                                                     low)(std::string, high))
