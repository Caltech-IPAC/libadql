#pragma once

#include "String_Value_Expression/Character_Factor.hxx"

namespace ADQL
{
using String_Value_Expression = std::vector<ADQL::Character_Factor>;

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::String_Value_Expression &string_value_expression)
{
  for (auto s = string_value_expression.begin ();
       s != string_value_expression.end ();)
    {
      os << *s;
      ++s;
      if (s != string_value_expression.end ())
        {
          os << " || ";
        }
    }
  return os;
}
}
