#pragma once

#include "../Column_Reference.hxx"
#include "Shape.hxx"

namespace ADQL
{
class Intersects
{
public:
  Column_Reference column;
  Shape shape;

  bool empty () const { return empty_variant (column); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Intersects& intersects)
{
  os << "INTERSECTS(" << intersects.column << "," << intersects.shape << ")";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Intersects,
                           (ADQL::Column_Reference, column)
                           (ADQL::Shape, shape))

