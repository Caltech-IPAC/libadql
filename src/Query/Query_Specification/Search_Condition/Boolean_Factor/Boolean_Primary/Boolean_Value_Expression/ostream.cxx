#include "../Boolean_Value_Expression.hxx"
#include "../../../../User_Defined_Function.hxx"

namespace ADQL
{
std::ostream &
operator<<(std::ostream &os,
           const ADQL::Boolean_Value_Expression &boolean_value_expression)
{
  return os << boolean_value_expression.variant;
}
}
