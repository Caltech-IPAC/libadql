#pragma once

#include "../Column_Reference.hxx"
#include "../Value_Expression_Wrap.hxx"
#include "Shape.hxx"
#include "XXX_or_Column.hxx"

namespace ADQL {
class Intersects {
public:
    Value_Expression_Wrap expression;
    Shape_or_Column shape_or_column_right;

    bool empty() const { return ADQL::empty(expression); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Intersects &intersects) {
    os << "INTERSECTS(" << intersects.expression << ","
       << intersects.shape_or_column_right << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Intersects,
                          (ADQL::Value_Expression_Wrap,
                           expression)(ADQL::Shape_or_Column, shape_or_column_right))
