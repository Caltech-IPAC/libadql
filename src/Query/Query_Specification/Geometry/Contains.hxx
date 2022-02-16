#pragma once

#include "../../empty_variant.hxx"
#include "../Column_Reference.hxx"
#include "Shape.hxx"

namespace ADQL {
class Contains {
public:
    typedef boost::variant<Point, Column_Reference> Point_or_Column;

    Point_or_Column point_or_column;
    Shape shape;

    bool empty() const { return empty_variant(point_or_column); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Contains &contains) {
    os << "CONTAINS(" << contains.point_or_column << "," << contains.shape << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Contains, (ADQL::Contains::Point_or_Column,
                                           point_or_column)(ADQL::Shape, shape))
