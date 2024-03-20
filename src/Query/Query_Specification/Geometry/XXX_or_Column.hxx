#pragma once

#include <boost/variant.hpp>

#include "../Column_Reference.hxx"
#include "Point.hxx"
#include "Shape.hxx"

namespace ADQL {
typedef boost::variant<Point, Column_Reference> Point_or_Column;
typedef boost::variant<Shape, Column_Reference> Shape_or_Column;
}  // namespace ADQL
