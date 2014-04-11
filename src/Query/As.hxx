#pragma once

#include <boost/fusion/include/io.hpp>
#include <iostream>
#include <string>

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

