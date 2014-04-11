#pragma once

#include "Predicate/Comparison_Predicate.hxx"

namespace ADQL
{
class Predicate
{
public:
  Comparison_Predicate comparison_predicate;
};
}

inline std::ostream & operator<<(std::ostream &os, const ADQL::Predicate &p)
{
  return os << p.comparison_predicate;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Predicate,
                           (ADQL::Comparison_Predicate, comparison_predicate))

