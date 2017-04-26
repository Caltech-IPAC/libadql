#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const std::vector<std::string> &v)
{
  os << "(";
  for (auto n = v.begin (); n != v.end ();)
    {
      os << *n;
      ++n;
      if (n != v.end ())
        os << ", ";
    }
  os << ")";
  return os;
}
}
