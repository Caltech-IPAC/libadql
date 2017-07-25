#pragma once

#include "Simple_Whens/Simple_When.hxx"

namespace ADQL
{
class Simple_Whens
{
public:
  std::vector<Simple_When> simple_whens;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Simple_Whens &simple_whens)
{
  for (auto &when : simple_whens.simple_whens)
    {
      os << when;
    }
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Simple_Whens,
                           (std::vector<ADQL::Simple_When>, simple_whens))
