#pragma once

#include "Geometry/Contains.hxx"

namespace ADQL
{
class Geometry
{
public:
  Contains contains;
  bool good() const
  {
    return !contains.point.coordinate.ra_dec(0).empty();
  }
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Geometry, (ADQL::Contains, contains))

