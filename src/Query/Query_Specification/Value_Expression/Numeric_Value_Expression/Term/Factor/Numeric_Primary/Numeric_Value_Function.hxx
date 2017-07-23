#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Numeric_Value_Function
{
public:
  std::string value;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Numeric_Value_Function &numeric_value_function)
{
  return os << numeric_value_function.value;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Value_Function, (std::string, value))
