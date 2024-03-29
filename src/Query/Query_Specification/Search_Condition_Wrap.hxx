#pragma once

#include <boost/variant/recursive_wrapper.hpp>
#include <iostream>

namespace ADQL {
class Search_Condition;
typedef boost::recursive_wrapper<Search_Condition> Search_Condition_Wrap;
bool empty(const Search_Condition_Wrap &s);
std::ostream &operator<<(std::ostream &os, const Search_Condition_Wrap &s);
}  // namespace ADQL
