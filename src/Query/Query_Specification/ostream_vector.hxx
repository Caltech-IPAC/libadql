#pragma once

#include <iostream>
#include <vector>

namespace ADQL
{
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
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
