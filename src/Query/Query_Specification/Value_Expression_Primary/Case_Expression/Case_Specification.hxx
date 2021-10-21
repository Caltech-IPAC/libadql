#pragma once

#include <boost/variant.hpp>

#include "../../../empty_variant.hxx"
#include "Case_Specification/Searched_Case.hxx"
#include "Case_Specification/Simple_Case.hxx"

namespace ADQL {
class Case_Specification {
public:
    typedef boost::variant<Simple_Case, Searched_Case> Variant;
    Variant variant;
    bool empty() const { return empty_variant(variant); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Case_Specification &case_specification) {
    return os << case_specification.variant;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Case_Specification,
                          (ADQL::Case_Specification::Variant, variant))
