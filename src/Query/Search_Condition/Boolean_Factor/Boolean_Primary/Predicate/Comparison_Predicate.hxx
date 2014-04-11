#pragma once

#include "../../../../Number_Variant.hxx"
namespace ADQL
{
class Comparison_Predicate
{
public:
  Number_Variant left, right;
  std::string op;
};
}

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Comparison_Predicate &c)
{
  return os << c.left << c.op << c.right;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Comparison_Predicate,
                           (ADQL::Number_Variant, left)
                           (std::string, op)
                           (ADQL::Number_Variant, right))

