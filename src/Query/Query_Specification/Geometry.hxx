#pragma once

#include "Geometry/Contains.hxx"
#include "Geometry/Intersects.hxx"

namespace ADQL
{
class Geometry
{
public:
  Contains contains;
  bool empty () const { return contains.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Geometry& geometry)
{
  if(!geometry.empty())
    os << geometry.contains;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Geometry, (ADQL::Contains, contains))
