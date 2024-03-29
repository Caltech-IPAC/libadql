#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <vector>

namespace ADQL {
class Value_Expression;
class Array_Constructor {
public:
    std::vector<Value_Expression> values;
    bool empty() const { return values.empty(); }
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Array_Constructor &array_constructor);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Array_Constructor,
                          (std::vector<ADQL::Value_Expression>, values))
