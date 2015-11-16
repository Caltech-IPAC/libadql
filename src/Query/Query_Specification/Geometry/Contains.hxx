#pragma once

#include "Point.hxx"
#include "Circle.hxx"
#include "Ellipse.hxx"
#include "Box.hxx"
#include "Polygon.hxx"

namespace ADQL
{
class Point_or_Column_empty_Visitor : public boost::static_visitor<bool>
{
public:
  bool operator () (const ADQL::Point &p) const
  {
    return p.empty ();
  }
  bool operator () (const std::string &s) const
  {
    return s.empty ();
  }
};

}


namespace ADQL
{
class Contains
{
public:
  typedef boost::variant<Circle, Box, Ellipse, Polygon> Shape;
  typedef boost::variant<Point, std::string> Point_or_Column;
  
  Point_or_Column point_or_column;
  Shape shape;

  bool empty () const
  {
    Point_or_Column_empty_Visitor visitor;
    return boost::apply_visitor (visitor, point_or_column);
  }
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

