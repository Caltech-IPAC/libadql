#pragma once
#include "Geometry/Contains.hxx"
#include "Non_Predicate_Geometry_Function_One_Arg.hxx"
#include "Non_Predicate_Geometry_Function_Two_Arg.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace ADQL {
class Non_Predicate_Geometry_Function {
public:
    typedef boost::variant<Non_Predicate_Geometry_Function_One_Arg,
                           Non_Predicate_Geometry_Function_Two_Arg>
            Variant;
    Variant variant;
    bool empty() const { return empty_variant(variant); }
};

inline std::ostream &operator<<(
        std::ostream &os,
        const ADQL::Non_Predicate_Geometry_Function &non_predicate_geometry_function) {
    return os << non_predicate_geometry_function.variant;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Non_Predicate_Geometry_Function,
                          (ADQL::Non_Predicate_Geometry_Function::Variant, variant))
