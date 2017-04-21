#pragma once

namespace ADQL
{
class Outer_Join
{
public:
  std::string type;
  bool outer=false;
};

inline std::ostream &operator<<(std::ostream &os, const Outer_Join &j)
{
  os << j.type;
  if (j.outer)
    os << " OUTER";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Outer_Join,
                           (std::string, type)
                           (bool, outer))
