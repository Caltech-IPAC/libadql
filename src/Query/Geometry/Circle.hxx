#pragma once

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
class Circle
{
public:
  Coord_Sys coord_sys;
  Coordinate center;
  double radius;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Circle, (ADQL::Coord_Sys,
                                          coord_sys)(ADQL::Coordinate,
                                                     center)(double, radius))
