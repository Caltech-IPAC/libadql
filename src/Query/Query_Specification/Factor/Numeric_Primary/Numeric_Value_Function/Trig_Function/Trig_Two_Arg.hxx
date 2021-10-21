#pragma once

#include "../../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Trig_Two_Arg {
public:
    std::string function;
    Value_Expression_Wrap arg0, arg1;
    bool empty() const { return function.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Trig_Two_Arg &trig_two_arg) {
    return os << trig_two_arg.function << "(" << trig_two_arg.arg0 << ","
              << trig_two_arg.arg1 << ")";
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Trig_Two_Arg,
                          (std::string, function)(ADQL::Value_Expression_Wrap,
                                                  arg0)(ADQL::Value_Expression_Wrap,
                                                        arg1))
