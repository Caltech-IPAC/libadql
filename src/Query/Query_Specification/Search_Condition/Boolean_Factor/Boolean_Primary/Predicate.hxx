#pragma once

#include "../../../../empty_variant.hxx"
#include "Predicate/Between_Predicate.hxx"
#include "Predicate/Comparison_Predicate.hxx"
#include "Predicate/Exists_Predicate.hxx"
#include "Predicate/In_Predicate.hxx"
#include "Predicate/Like_Predicate.hxx"
#include "Predicate/Null_Predicate.hxx"

namespace ADQL {
class Predicate {
public:
    typedef boost::variant<Comparison_Predicate, Between_Predicate, In_Predicate,
                           Null_Predicate, Like_Predicate, Exists_Predicate>
            Variant;
    Variant variant;
    bool empty() const { return empty_variant(variant); }
};
}  // namespace ADQL

namespace ADQL {
inline std::ostream &operator<<(std::ostream &os, const ADQL::Predicate &p) {
    return os << p.variant;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Predicate, (ADQL::Predicate::Variant, variant))
