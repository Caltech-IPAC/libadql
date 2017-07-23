#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class User_Defined_Function
{
public:
  std::string value;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::User_Defined_Function &user_defined_function)
{
  return os << user_defined_function.value;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::User_Defined_Function, (std::string, value))
