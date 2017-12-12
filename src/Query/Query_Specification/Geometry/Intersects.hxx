#pragma once

#include "../Column_Reference.hxx"
#include "Shape.hxx"

namespace ADQL
{
class Intersects
{
public:
  Value_Expression_Wrap expression;
  Shape shape;

  bool empty () const { return ADQL::empty (expression); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Intersects &intersects)
{
  os << "INTERSECTS(" << intersects.expression << "," << intersects.shape << ")";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Intersects, (ADQL::Value_Expression_Wrap,
                            expression)(ADQL::Shape, shape))
