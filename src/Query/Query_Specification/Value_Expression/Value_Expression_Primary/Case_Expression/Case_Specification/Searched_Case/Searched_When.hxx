#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Searched_When
{
public:
  std::string searched_when;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Searched_When &searched_when)
{
  return os << searched_when.searched_when;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Searched_When, (std::string, searched_when))
