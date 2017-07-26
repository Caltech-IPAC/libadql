#pragma once

#include "Searched_Whens/Searched_When.hxx"

namespace ADQL
{
class Searched_Whens
{
public:
  std::vector<Searched_When> whens;
  bool empty () const { return whens.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Searched_Whens &searched_whens)
{
  for (auto &when : searched_whens.whens)
    {
      os << when << " ";
    }
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Searched_Whens,
                           (std::vector<ADQL::Searched_When>, whens))
