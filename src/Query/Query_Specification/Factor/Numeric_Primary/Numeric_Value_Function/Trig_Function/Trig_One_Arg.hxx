#pragma once

#include "../../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Trig_One_Arg {
public:
    std::string function;
    Value_Expression_Wrap arg;
    bool empty() const { return function.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Trig_One_Arg &trig_one_arg) {
    return os << trig_one_arg.function << "(" << trig_one_arg.arg << ")";
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Trig_One_Arg,
                          (std::string, function)(ADQL::Value_Expression_Wrap, arg))
