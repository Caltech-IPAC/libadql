#pragma once

#include <vector>
#include "Coord_Sys.hxx"
#include "Coordinate.hxx"

namespace ADQL {
class Polygon {
public:
    Coord_Sys coord_sys;
    std::vector<Coordinate> coordinates;

    bool empty() const { return coordinates.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Polygon &polygon) {
    os << "POLYGON(\'" << polygon.coord_sys << "\'";
    for (auto &c : polygon.coordinates) os << "," << c;
    os << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Polygon,
                          (ADQL::Coord_Sys, coord_sys)(std::vector<ADQL::Coordinate>,
                                                       coordinates))
