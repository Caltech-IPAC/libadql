#pragma once
#include <boost/variant/recursive_wrapper.hpp>
#include <iostream>

namespace ADQL {
class Window_Function;
typedef boost::recursive_wrapper<Window_Function> Window_Function_Wrap;
bool empty(const Window_Function_Wrap &s);
std::ostream &operator<<(std::ostream &os, const Window_Function_Wrap &s);
}  // namespace ADQL
