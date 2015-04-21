#pragma once

#include "../../../../../Subquery.hxx"

namespace ADQL
{
class Exists_Predicate
{
public:
  Subquery subquery;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Exists_Predicate &c)
{
  return os << "EXISTS " << c.subquery;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Exists_Predicate,
                           (ADQL::Subquery, subquery))
