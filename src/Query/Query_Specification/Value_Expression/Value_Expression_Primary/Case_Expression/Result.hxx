#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Result
{
public:
  std::string result;
  bool empty () const { return result.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Result &result)
{
  return os << result.result << " ";
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Result, (std::string, result))
