#ifndef ADQL_COORD_SYS_HXX
#define ADQL_COORD_SYS_HXX

#include <boost/fusion/include/adapt_struct.hpp>

namespace ADQL
{
  class Coord_Sys
  {
  public:
    enum class Reference_Frame {J2000, ICRS} frame;
    enum class Reference_Position {GEOCENTER} position;
  };
}

BOOST_FUSION_ADAPT_STRUCT(ADQL::Coord_Sys,
                          (ADQL::Coord_Sys::Reference_Frame, frame)
                          (ADQL::Coord_Sys::Reference_Position, position))

#endif
