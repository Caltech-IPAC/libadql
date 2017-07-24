#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Array_Constructor
{
public:
  std::string expression;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Array_Constructor &array_constructor)
{
  return os << array_constructor.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Array_Constructor,
                           (std::string, expression))
