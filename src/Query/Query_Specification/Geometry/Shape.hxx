#pragma once

#include "../Column_Reference.hxx"
#include "Box.hxx"
#include "Circle.hxx"
#include "Ellipse.hxx"
#include "Point.hxx"
#include "Polygon.hxx"

namespace ADQL {
typedef boost::variant<Point, Circle, Box, Ellipse, Polygon> Shape;
typedef boost::variant<Shape, Column_Reference> Shape_or_Column;
}  // namespace ADQL
