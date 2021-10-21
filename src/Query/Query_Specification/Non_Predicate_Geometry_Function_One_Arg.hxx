#pragma once
#include "Geometry/Contains.hxx"
namespace ADQL {
class Non_Predicate_Geometry_Function_One_Arg {
public:
    std::string function;
    ADQL::Contains::Point_or_Column arg;
    bool empty() const { return function.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Non_Predicate_Geometry_Function_One_Arg
                                        &non_predicate_geometry_function_one_arg) {
    if (!non_predicate_geometry_function_one_arg.empty())
        return os << non_predicate_geometry_function_one_arg.function << "("
                  << non_predicate_geometry_function_one_arg.arg << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Non_Predicate_Geometry_Function_One_Arg,
                          (std::string, function)(ADQL::Contains::Point_or_Column, arg))
