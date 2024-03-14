#pragma once

#include "Column_or_Simple_Arithmetic_Expression.hxx"
#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL {
class Box {
public:
    Coord_Sys coord_sys;
    Coordinate center;
    Column_or_Simple_Arithmetic_Expression width, height;

    bool empty() const { return center.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Box &box) {
    os << "BOX(\'" << box.coord_sys << "\'," << box.center << "," << box.width << ","
       << box.height << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Box,
                          (ADQL::Coord_Sys, coord_sys)(ADQL::Coordinate, center)(
                                  ADQL::Column_or_Simple_Arithmetic_Expression,
                                  width)(ADQL::Column_or_Simple_Arithmetic_Expression,
                                         height))
