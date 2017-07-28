#include "../Value_Expression_Non_Bool_Wrap.hxx"
#include "../Value_Expression_Non_Bool.hxx"

namespace ADQL
{
bool empty (const Value_Expression_Non_Bool_Wrap &wrap)
{
  return wrap.get ().empty ();
}
}
