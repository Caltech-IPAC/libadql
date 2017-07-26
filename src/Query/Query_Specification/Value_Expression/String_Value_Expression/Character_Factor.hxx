#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Character_Factor
{
public:
  std::string factor;
  bool empty () const { return factor.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Character_Factor &character_factor)
{
  return os << character_factor.factor;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Character_Factor, (std::string, factor))
