#include "../Boolean_Primary.hxx"
#include "../../../Search_Condition.hxx"
#include "../../../Value_Expression_Primary.hxx"
#include "../../../../empty_variant.hxx"

bool ADQL::Boolean_Primary::empty () const
{
  return empty_variant (variant);
}
