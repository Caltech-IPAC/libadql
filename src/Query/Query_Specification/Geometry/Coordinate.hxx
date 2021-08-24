#pragma once

#include <string>
#include <boost/fusion/include/adapt_struct.hpp>
#include "Column_or_Simple_Arithmetic_Expression.hxx"

namespace ADQL
{
struct Coordinate
{
public:
  Column_or_Simple_Arithmetic_Expression ra, dec;

  /// We can not use ADQL::empty_variant because double does not have
  /// an empty() method.
  bool empty () const
  {
    Column_or_Simple_Arithmetic_Expression_empty_Visitor visitor;
    return boost::apply_visitor (visitor, ra);
  }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Coordinate &coordinate)
{
  os << coordinate.ra << "," << coordinate.dec;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Coordinate, (ADQL::Column_or_Simple_Arithmetic_Expression,
                                              ra)(ADQL::Column_or_Simple_Arithmetic_Expression, dec))
