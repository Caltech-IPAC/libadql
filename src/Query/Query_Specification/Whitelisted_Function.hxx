#pragma once

#include <iostream>
#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include "Value_Expression.hxx"

namespace ADQL {
class Whitelisted_Function {
public:
    std::string function;
    std::vector<ADQL::Value_Expression> args;
    bool empty() const { return function.empty(); }
};

inline std::ostream &operator<<(
        std::ostream &os, const ADQL::Whitelisted_Function &whitelisted_function) {
    os << whitelisted_function.function << '(';
    for (auto a = whitelisted_function.args.begin();
         a != whitelisted_function.args.end();) {
        os << *a;
        ++a;
        if (a != whitelisted_function.args.end()) {
            os << ',';
        }
    }
    os << ')';
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Whitelisted_Function,
                          (std::string, function)(std::vector<ADQL::Value_Expression>,
                                                  args))
