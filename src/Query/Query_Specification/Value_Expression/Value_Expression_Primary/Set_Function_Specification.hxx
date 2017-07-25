#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Set_Function_Specification
{
public:
  std::string expression;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Set_Function_Specification &set_function_specification)
{
  return os << set_function_specification.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Set_Function_Specification,
                           (std::string, expression))
