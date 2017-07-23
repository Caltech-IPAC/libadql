#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Factor
{
public:
  std::string sign, numeric_primary;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Factor &factor)
{
  return os << factor.sign << factor.numeric_primary;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Factor,
                           (std::string, sign)(std::string, numeric_primary))
