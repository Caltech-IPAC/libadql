#pragma once
#include "Geometry/Contains.hxx"
namespace ADQL {
class Non_Predicate_Geometry_Function_Two_Arg {
public:
    std::string function;
    ADQL::Contains::Point_or_Column arg0;
    ADQL::Contains::Point_or_Column arg1;
    bool empty() const { return function.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Non_Predicate_Geometry_Function_Two_Arg
                                        &non_predicate_geometry_function_two_arg) {
    if (!non_predicate_geometry_function_two_arg.empty())
        return os << non_predicate_geometry_function_two_arg.function << "("
                  << non_predicate_geometry_function_two_arg.arg0 << ','
                  << non_predicate_geometry_function_two_arg.arg1 << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Non_Predicate_Geometry_Function_Two_Arg,
                          (std::string, function)(ADQL::Contains::Point_or_Column,
                                                  arg0)(ADQL::Contains::Point_or_Column,
                                                        arg1))
