#include "../Numeric_Value_Function.hxx"
#include "../../../../../User_Defined_Function.hxx"
#include "../../../../../../empty_variant.hxx"

bool ADQL::Numeric_Value_Function::empty () const
{
  return empty_variant (variant);
}
