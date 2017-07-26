#pragma once

#include "Searched_Whens/Searched_When.hxx"

#include <vector>

namespace ADQL
{
using Searched_Whens = std::vector<Searched_When>;

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Searched_Whens &searched_whens)
{
  for (auto &when : searched_whens)
    {
      os << when << " ";
    }
  return os;
}
}
