#pragma once

#include "Geometry.hxx"
#include "Search_Condition.hxx"

namespace ADQL
{
class Where
{
public:
  Search_Condition search_condition;
  Geometry geometry;
};
}

inline std::ostream & operator<<(std::ostream &os, const ADQL::Where &w)
{
  if(w.search_condition.good())
    return os << "WHERE " << w.search_condition;
  return os;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Where,
                           (ADQL::Geometry, geometry)
                           (ADQL::Search_Condition, search_condition))
