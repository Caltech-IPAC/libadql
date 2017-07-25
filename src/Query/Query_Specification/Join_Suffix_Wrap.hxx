#pragma once

#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL
{
class Join_Suffix;
typedef boost::recursive_wrapper<Join_Suffix> Join_Suffix_Wrap;
bool empty (const Join_Suffix_Wrap &s);
std::ostream &operator<<(std::ostream &os, const Join_Suffix_Wrap &s);
}
