#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Math_Zero_Arg
{
public:
  std::string function;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Math_Zero_Arg &math_zero_arg)
{
  return os << math_zero_arg.function << "()";
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Math_Zero_Arg, (std::string, function))
