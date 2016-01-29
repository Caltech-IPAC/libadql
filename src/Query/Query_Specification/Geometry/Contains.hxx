#pragma once

#include "Point.hxx"
#include "Circle.hxx"
#include "Ellipse.hxx"
#include "Box.hxx"
#include "Polygon.hxx"
#include "../../empty_variant.hxx"

namespace ADQL
{
class Contains
{
public:
  typedef boost::variant<Circle, Box, Ellipse, Polygon> Shape;
  typedef boost::variant<Point, std::string> Point_or_Column;
  
  Point_or_Column point_or_column;
  Shape shape;

  bool empty () const { return empty_variant (point_or_column); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Contains& contains)
{
  os << "CONTAINS(" << contains.point_or_column << "," << contains.shape << ")=1";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Contains,
                           (ADQL::Contains::Point_or_Column, point_or_column)
                           (ADQL::Contains::Shape, shape))

