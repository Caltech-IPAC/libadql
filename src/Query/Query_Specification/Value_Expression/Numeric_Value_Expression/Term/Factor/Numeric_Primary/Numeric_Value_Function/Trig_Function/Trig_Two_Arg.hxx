#pragma once

#include "../../../../../Numeric_Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Trig_Two_Arg
{
public:
  std::string function;
  Numeric_Value_Expression_Wrap arg0, arg1;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Trig_Two_Arg &trig_two_arg)
{
  return os << trig_two_arg.function << "(" << trig_two_arg.arg0 << ","
            << trig_two_arg.arg1 << ")";
}
}

BOOST_FUSION_ADAPT_STRUCT (
    ADQL::Trig_Two_Arg,
    (std::string, function)(ADQL::Numeric_Value_Expression_Wrap,
                            arg0)(ADQL::Numeric_Value_Expression_Wrap, arg1))
