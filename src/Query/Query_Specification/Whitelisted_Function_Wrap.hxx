#pragma once

#include <boost/variant/recursive_wrapper.hpp>
#include <iostream>

namespace ADQL {
class Whitelisted_Function;
typedef boost::recursive_wrapper<Whitelisted_Function> Whitelisted_Function_Wrap;
std::ostream &operator<<(std::ostream &os, const Whitelisted_Function_Wrap &s);
}  // namespace ADQL
