#pragma once

#include "../Subquery.hxx"

namespace ADQL {
class Derived_Correlation {
public:
    Subquery subquery;
    std::string as;
    bool empty() const { return subquery.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Derived_Correlation &d) {
    os << d.subquery;
    if (!d.as.empty()) os << " " << d.as;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Derived_Correlation,
                          (ADQL::Subquery, subquery)(std::string, as))
