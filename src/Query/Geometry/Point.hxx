#pragma once

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
struct Point
{
public:
  Coord_Sys coord_sys;
  Coordinate coordinate;
};
}

namespace std
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Point& point)
{
  os << "POINT(\'" << point.coord_sys << "\'," << point.coordinate << ")";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Point,
                           (ADQL::Coord_Sys, coord_sys)(ADQL::Coordinate,
                                                        coordinate))

