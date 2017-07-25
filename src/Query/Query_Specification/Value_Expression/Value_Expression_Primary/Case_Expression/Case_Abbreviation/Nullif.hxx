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
  std::string nullif;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Nullif &nullif)
{
  return os << nullif.nullif;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Nullif, (std::string, nullif))
