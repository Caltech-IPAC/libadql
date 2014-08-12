#pragma once

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
class Polygon
{
public:
  Coord_Sys coord_sys;
  std::vector<Coordinate> coordinates;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Polygon,
                           (ADQL::Coord_Sys,
                            coord_sys)
                           (std::vector<ADQL::Coordinate>,
                            coordinates))
