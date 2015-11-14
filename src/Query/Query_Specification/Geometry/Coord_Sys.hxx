#pragma once

#include <iostream>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ADQL
{
class Coord_Sys
{
public:
  enum class Reference_Frame
  { J2000, ICRS, Galactic } frame;
      
  enum class Reference_Position
  { GEOCENTER } position;

  std::string string () const;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Coord_Sys &c)
{
  switch (c.frame)
    {
    case ADQL::Coord_Sys::Reference_Frame::J2000:
      os << "J2000";
      break;
    case ADQL::Coord_Sys::Reference_Frame::ICRS:
      os << "ICRS";
      break;
    case ADQL::Coord_Sys::Reference_Frame::Galactic:
      os << "GALACTIC";
      break;
    }
  os << " GEOCENTER";
  return os;
}
}

inline std::string ADQL::Coord_Sys::string () const
{
  std::stringstream ss;
  ss << *this;
  return ss.str ();
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Coord_Sys,
                           (ADQL::Coord_Sys::Reference_Frame,
                            frame)(ADQL::Coord_Sys::Reference_Position,
                                   position))

