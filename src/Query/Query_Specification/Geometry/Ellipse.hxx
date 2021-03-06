#pragma once

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
class Ellipse
{
public:
  Coord_Sys coord_sys;
  Coordinate center;
  Column_or_Number semi_major_axis, ratio, rotation;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Ellipse &ellipse)
{
  os << "ELLIPSE(\'" << ellipse.coord_sys << "\'," << ellipse.center << ","
     << ellipse.semi_major_axis << "," << ellipse.ratio << ","
     << ellipse.rotation << ")";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Ellipse,
                           (ADQL::Coord_Sys, coord_sys)(ADQL::Coordinate,
                                                        center)(
                               ADQL::Column_or_Number,
                               semi_major_axis)(ADQL::Column_or_Number,
                                                ratio)(ADQL::Column_or_Number,
                                                       rotation))
