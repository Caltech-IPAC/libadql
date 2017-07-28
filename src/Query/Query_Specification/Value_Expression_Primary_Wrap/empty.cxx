#include "../Value_Expression_Primary_Wrap.hxx"
#include "../Value_Expression_Primary.hxx"

namespace ADQL
{
bool empty (const Value_Expression_Primary_Wrap &wrap)
{
  return wrap.get ().empty ();
}
}
