#pragma once

#include <boost/variant/recursive_wrapper.hpp>

namespace ADQL
{
class Search_Condition;
typedef boost::recursive_wrapper<Search_Condition> Search_Condition_Wrap;
}

