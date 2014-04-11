#pragma once

#include "Boolean_Primary/Predicate.hxx"

namespace ADQL
{
class Boolean_Primary
{
public:
  Predicate predicate;
};
}

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Boolean_Primary &b)
{
  return os << b.predicate;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Boolean_Primary,
                           (ADQL::Predicate, predicate))

