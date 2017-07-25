#pragma once

#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL
{
class Value_Expression;
typedef boost::recursive_wrapper<Value_Expression> Value_Expression_Wrap;
std::ostream &operator<<(std::ostream &os, const Value_Expression_Wrap &s);
}
