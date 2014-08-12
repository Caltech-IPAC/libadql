#pragma once

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
class Box
{
public:
  Coord_Sys coord_sys;
  Coordinate center;
  double width, height;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Box,
                           (ADQL::Coord_Sys,
                            coord_sys)(ADQL::Coordinate,
                                       center)(double, width)(double, height))
