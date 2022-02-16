#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include "Column_or_Simple_Arithmetic_Expression.hxx"

namespace ADQL {
struct Coordinate {
    Column_or_Simple_Arithmetic_Expression ra, dec;
    bool empty() const { return ra.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Coordinate &coordinate) {
    os << coordinate.ra << "," << coordinate.dec;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Coordinate,
                          (ADQL::Column_or_Simple_Arithmetic_Expression,
                           ra)(ADQL::Column_or_Simple_Arithmetic_Expression, dec))
