#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Nullif
{
public:
  std::string arg0, arg1;
  bool empty () const { return arg0.empty (); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Nullif &nullif)
{
  return os << "NULLIF(" << nullif.arg0 << ',' << nullif.arg1 << ')';
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Nullif,
                           (std::string, arg0)(std::string, arg1))
