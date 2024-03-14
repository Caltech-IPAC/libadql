#pragma once

#include "../../empty_variant.hxx"
#include "../Column_Reference.hxx"
#include "Shape.hxx"

namespace ADQL {
class Contains {
public:
    // JTODO move this
    typedef boost::variant<Point, Column_Reference> Point_or_Column;

    Shape_or_Column shape_or_column_left;
    Shape_or_Column shape_or_column_right;

    bool empty() const {
        return empty_variant(shape_or_column_left) ||
               empty_variant(shape_or_column_right);
    }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Contains &contains) {
    os << "CONTAINS(" << contains.shape_or_column_left << ","
       << contains.shape_or_column_right << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Contains, (ADQL::Shape_or_Column,
                                           shape_or_column_left)(ADQL::Shape_or_Column,
                                                                 shape_or_column_right))
