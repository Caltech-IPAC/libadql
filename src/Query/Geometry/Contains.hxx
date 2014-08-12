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
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Contains,
                           (ADQL::Point, point)(ADQL::Contains::Shape, shape))

