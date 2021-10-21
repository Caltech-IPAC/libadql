#pragma once

#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL {
class Value_Expression_Non_Bool;
typedef boost::recursive_wrapper<Value_Expression_Non_Bool>
        Value_Expression_Non_Bool_Wrap;
std::ostream &operator<<(std::ostream &os, const Value_Expression_Non_Bool_Wrap &s);
bool empty(const Value_Expression_Non_Bool_Wrap &);
}  // namespace ADQL
