#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Math_Zero_Arg {
public:
    std::string function;
    bool empty() const { return function.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Math_Zero_Arg &math_zero_arg) {
    return os << math_zero_arg.function << "()";
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Math_Zero_Arg, (std::string, function))
