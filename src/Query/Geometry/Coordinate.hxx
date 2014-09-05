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

namespace std
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Coordinate& coordinate)
{
  os << coordinate.ra << "," << coordinate.dec;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Coordinate,
                           (std::string, ra)(std::string, dec))
