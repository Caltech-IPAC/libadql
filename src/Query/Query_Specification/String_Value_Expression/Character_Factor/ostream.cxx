#include "../Character_Factor.hxx"
#include "../../Value_Expression_Primary.hxx"
#include "../../User_Defined_Function.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Character_Factor &character_factor)
{
  return os << character_factor.variant;
}
}
