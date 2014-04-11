#pragma once

#include <string>
#include "boost/variant.hpp"

namespace ADQL
{
typedef boost::variant<std::string, double> Number_Variant;
}
