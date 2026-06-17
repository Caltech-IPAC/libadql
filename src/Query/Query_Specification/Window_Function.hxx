#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include "Value_Expression.hxx"

namespace ADQL {
class Window_Function {
public:
    std::string function_name;
    std::vector<ADQL::Value_Expression> partition_by;
    std::vector<ADQL::Value_Expression> order_by;
    bool empty() const { return function_name.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Window_Function &window_function) {
    os << window_function.function_name << "() OVER (PARTITION BY ";
    for (auto p = window_function.partition_by.begin();
         p != window_function.partition_by.end();) {
        os << *p;
        ++p;
        if (p != window_function.partition_by.end()) os << ", ";
    }
    os << " ORDER BY ";
    for (auto o = window_function.order_by.begin();
         o != window_function.order_by.end();) {
        os << *o;
        ++o;
        if (o != window_function.order_by.end()) os << ", ";
    }
    os << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Window_Function,
    (std::string, function_name)
    (std::vector<ADQL::Value_Expression>, partition_by)
    (std::vector<ADQL::Value_Expression>, order_by))
