#ifndef ADQL_COORD_SYS_HXX
#define ADQL_COORD_SYS_HXX

namespace ADQL
{
  class Coord_Sys
  {
  public:
    enum class Reference_Frame {J2000, ICRS} frame;
    enum class Reference_Position {GEOCENTER} position;
  };
}
#endif
