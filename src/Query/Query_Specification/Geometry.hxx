#pragma once

#include "Geometry/Contains.hxx"
#include "Geometry/Intersects.hxx"

namespace ADQL {
class Geometry {
public:
    typedef boost::variant<Intersects, Contains> Predicate;
    Predicate predicate;
    bool empty() const { return empty_variant(predicate); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Geometry &geometry) {
    if (!geometry.empty()) os << geometry.predicate;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Geometry, (ADQL::Geometry::Predicate, predicate))
