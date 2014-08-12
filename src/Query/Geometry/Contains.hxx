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
  Point point;
  Circle circle;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Contains,
                           (ADQL::Point, point)(ADQL::Circle, circle))

