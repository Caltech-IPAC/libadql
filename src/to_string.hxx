#pragma once

#include <sstream>
#include <string>

namespace ADQL
{
template <class T> inline std::string to_string (const T &t)
{
  std::stringstream ss;
  ss.precision (17);
  ss << t;
  return ss.str ();
}
}
