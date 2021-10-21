#pragma once

#include "../../../empty_variant.hxx"
#include "Case_Abbreviation/Coalesce.hxx"
#include "Case_Abbreviation/Nullif.hxx"

#include <boost/variant.hpp>

namespace ADQL {
class Case_Abbreviation {
public:
    typedef boost::variant<Nullif, Coalesce> Variant;
    Variant variant;
    bool empty() const { return empty_variant(variant); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Case_Abbreviation &case_abbreviation) {
    return os << case_abbreviation.variant;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Case_Abbreviation,
                          (ADQL::Case_Abbreviation::Variant, variant))
