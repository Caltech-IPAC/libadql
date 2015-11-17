#pragma once

#include <sstream>
#include <string>

namespace ADQL
{
template <class T>
inline std::string to_string (const T& t)
{
  std::stringstream ss;
  ss.precision (15);
  ss << t;
  return ss.str();
}
}
