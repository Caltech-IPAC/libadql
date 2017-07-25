#include "../Result.hxx"
#include "../../../../Value_Expression.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os, const ADQL::Result &result)
{
  return os << result.variant;
}
}
