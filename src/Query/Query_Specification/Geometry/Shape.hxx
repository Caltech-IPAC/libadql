#pragma once

#include "Box.hxx"
#include "Circle.hxx"
#include "Ellipse.hxx"
#include "Point.hxx"
#include "Polygon.hxx"

namespace ADQL {
typedef boost::variant<Point, Circle, Box, Ellipse, Polygon> Shape;

}  // namespace ADQL
