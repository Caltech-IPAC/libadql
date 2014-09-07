#pragma once

#include "Point.hxx"
#include "Circle.hxx"
#include "Ellipse.hxx"
#include "Box.hxx"
#include "Polygon.hxx"

namespace ADQL
{
class Contains
{
public:
  typedef boost::variant<Circle, Box, Ellipse, Polygon> Shape;

  Point point;
  Shape shape;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Contains& contains)
{
  os << "CONTAINS(" << contains.point << "," << contains.shape << ")=1";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Contains,
                           (ADQL::Point, point)(ADQL::Contains::Shape, shape))

