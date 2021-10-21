#pragma once

#include "../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Value_Subexpression {
public:
    Value_Expression_Wrap wrap;
    bool empty() const { return ADQL::empty(wrap); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Value_Subexpression &value_subexpression) {
    return os << '(' << value_subexpression.wrap << ')';
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Value_Subexpression,
                          (ADQL::Value_Expression_Wrap, wrap))
