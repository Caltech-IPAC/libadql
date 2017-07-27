#include "../Value_Expression.hxx"

namespace ADQL
{
bool empty (const Value_Expression_Wrap &wrap)
{
  return wrap.get ().empty ();
}
}
