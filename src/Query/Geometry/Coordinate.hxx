#pragma once

#include <string>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ADQL
{
struct Coordinate
{
public:
  std::string ra, dec;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Coordinate,
                           (std::string, ra)(std::string, dec))
