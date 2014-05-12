#pragma once

#include "Geometry/Contains.hxx"

namespace ADQL
{
class Geometry
{
public:
  Contains contains;
  bool empty () const { return contains.point.coordinate.ra.empty (); }
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Geometry, (ADQL::Contains, contains))
