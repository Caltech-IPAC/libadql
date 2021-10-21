#pragma once

#include "../../empty_variant.hxx"
#include "Join_Specification/Join_Condition.hxx"
#include "Join_Specification/Named_Columns_Join.hxx"

namespace ADQL {
class Join_Specification {
public:
    typedef boost::variant<Named_Columns_Join, Join_Condition> Variant;
    Variant variant;
    bool empty() const { return empty_variant(variant); }
};
}  // namespace ADQL

namespace ADQL {
inline std::ostream &operator<<(std::ostream &os, const ADQL::Join_Specification &j) {
    return os << j.variant;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Join_Specification,
                          (ADQL::Join_Specification::Variant, variant))
