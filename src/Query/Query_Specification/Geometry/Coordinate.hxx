#pragma once

#include <string>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Column_or_Number.hxx"

namespace ADQL
{
struct Coordinate
{
public:
  Column_or_Number ra, dec;

  bool empty () const
  {
    Column_or_Number_empty_Visitor visitor;
    return boost::apply_visitor (visitor, ra);
  }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Coordinate& coordinate)
{
  os << coordinate.ra << "," << coordinate.dec;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Coordinate,
                           (ADQL::Column_or_Number, ra)
                           (ADQL::Column_or_Number, dec))
