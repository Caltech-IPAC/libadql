#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class General_Set_Function
{
public:
  std::string general;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::General_Set_Function &general_set_function)
{
  return os << general_set_function.general;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::General_Set_Function, (std::string, general))
