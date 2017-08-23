#pragma once

#include "../../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Math_One_Arg
{
public:
  std::string function;
  Value_Expression_Wrap arg;
  bool empty () const { return function.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Math_One_Arg &math_one_arg)
{
  return os << math_one_arg.function << "(" << math_one_arg.arg << ")";
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Math_One_Arg,
                           (std::string,
                            function)(ADQL::Value_Expression_Wrap,
                                      arg))
