#pragma once

#include "Boolean_Factor/Boolean_Primary.hxx"

namespace ADQL {
class Boolean_Factor {
public:
    std::string Not;
    Boolean_Primary boolean_primary;
    bool empty() const { return boolean_primary.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Boolean_Factor &b) {
    return os << b.Not << (b.Not.empty() ? "" : " ") << b.boolean_primary;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Boolean_Factor,
                          (std::string, Not)(ADQL::Boolean_Primary, boolean_primary))
