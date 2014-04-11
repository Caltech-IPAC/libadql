#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ADQL
{
class As
{
public:
  std::string expression, as;
};

inline std::ostream & operator<<(std::ostream &os, const As &as)
{
  return os << as.expression << " AS " << as.as;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::As,
                           (std::string, expression)
                           (std::string, as))

