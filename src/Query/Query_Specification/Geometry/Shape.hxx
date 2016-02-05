#pragma once

#include "Point.hxx"
#include "Circle.hxx"
#include "Ellipse.hxx"
#include "Box.hxx"
#include "Polygon.hxx"

namespace ADQL
{
typedef boost::variant<Point, Circle, Box, Ellipse, Polygon> Shape;
}
