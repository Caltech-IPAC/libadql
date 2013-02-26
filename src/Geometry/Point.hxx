#ifndef ADQL_POINT_HXX
#define ADQL_POINT_HXX

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
  class Point
  {
  public:
    Coord_Sys coord_sys;
    Coordinate coordinate;
  };
}

#endif
