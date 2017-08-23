#pragma once

#include "../../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Math_Two_Arg
{
public:
  std::string function;
  Value_Expression_Wrap arg0, arg1;
  bool empty () const { return function.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Math_Two_Arg &math_two_arg)
{
  return os << math_two_arg.function << "(" << math_two_arg.arg0 << ","
            << math_two_arg.arg1 << ")";
}
}

BOOST_FUSION_ADAPT_STRUCT (
    ADQL::Math_Two_Arg,
    (std::string, function)(ADQL::Value_Expression_Wrap,
                            arg0)(ADQL::Value_Expression_Wrap, arg1))
