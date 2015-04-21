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
  bool empty() const
  {
    return geometry.empty() && search_condition.empty();
  }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Where& where)
{
  if(!where.geometry.empty())
    {
      os << where.geometry;
      if(!where.search_condition.empty())
        os << " AND (" << where.search_condition << ")";
    }
  else if(!where.search_condition.empty())
    os << where.search_condition;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Where,
                           (ADQL::Geometry, geometry)(ADQL::Search_Condition,
                                                      search_condition))
