#include "../Character_Factor.hxx"
#include "../../Value_Expression_Primary.hxx"
#include "../../User_Defined_Function.hxx"
#include "../../../empty_variant.hxx"

namespace ADQL
{
bool ADQL::Character_Factor::empty () const { return empty_variant (variant); }
}
