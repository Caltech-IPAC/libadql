#include "../Numeric_Value_Function.hxx"
#include "../../../../../User_Defined_Function.hxx"

namespace ADQL
{
std::ostream &
operator<<(std::ostream &os,
           const ADQL::Numeric_Value_Function &numeric_value_function)
{
  return os << numeric_value_function.variant;
}
}
