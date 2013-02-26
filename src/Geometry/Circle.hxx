#ifndef ADQL_CIRCLE_HXX
#define ADQL_CIRCLE_HXX

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
  class Circle
  {
  public:
    Coord_Sys coord_sys;
    Coordinate coordinate;
    double radius;
  };
}

#endif
