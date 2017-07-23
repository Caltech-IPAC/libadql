#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Math_Function
{
public:
  std::string value;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Math_Function &math_function)
{
  return os << math_function.value;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Math_Function, (std::string, value))
