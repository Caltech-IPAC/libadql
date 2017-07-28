#pragma once

#include "String_Value_Expression.hxx"

namespace ADQL
{
using String_Value_Expression_Wrap = String_Value_Expression;
inline bool empty (const String_Value_Expression_Wrap &s)
{
  return s.empty ();
}
}
