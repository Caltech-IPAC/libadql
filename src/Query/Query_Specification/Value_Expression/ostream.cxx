#include "../Value_Expression.hxx"
#include "../Search_Condition.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Value_Expression &value_expression)
{
  return os << value_expression.variant;
}
}
