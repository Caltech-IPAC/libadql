#pragma once

#include "Circle.hxx"
#include "Ellipse.hxx"
#include "Box.hxx"
#include "Polygon.hxx"

namespace ADQL
{
class Intersects
{
public:
  typedef boost::variant<Point, Circle, Box, Ellipse, Polygon> Shape;
  
  std::string column;
  Shape shape;

  bool empty () const
  {
    return column.empty ();
  }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Intersects& contains)
{
  os << "INTERSECTS(" << contains.column << "," << contains.shape << ")";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Intersects,
                           (std::string, column)
                           (ADQL::Intersects::Shape, shape))

