#pragma once

#include "../../../../Value_Expression.hxx"

namespace ADQL
{
class Comparison_Predicate
{
public:
  Value_Expression left, right;
  std::string op;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Comparison_Predicate &c)
{
  return os << c.left << " " << c.op << " " << c.right;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Comparison_Predicate,
                           (ADQL::Value_Expression,
                            left)(std::string, op)(ADQL::Value_Expression,
                                                   right))
