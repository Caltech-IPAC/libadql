#ifndef ADQL_POINT_HXX
#define ADQL_POINT_HXX

#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL
{
  struct Point
  {
  public:
    // Coord_Sys coord_sys;
    std::string coord_sys;
    Coordinate coordinate;
  };
}

BOOST_FUSION_ADAPT_STRUCT(ADQL::Point,
                          (std::string, coord_sys)
                          (ADQL::Coordinate, coordinate))


#endif
