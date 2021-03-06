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
  Column_or_Number radius;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Circle &circle)
{
  os << "CIRCLE(\'" << circle.coord_sys << "\'," << circle.center << ","
     << circle.radius << ")";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Circle,
                           (ADQL::Coord_Sys,
                            coord_sys)(ADQL::Coordinate,
                                       center)(ADQL::Column_or_Number, radius))
