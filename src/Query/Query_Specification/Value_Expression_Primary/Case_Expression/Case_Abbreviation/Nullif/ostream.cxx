#include "../Nullif.hxx"
#include "../../../../Value_Expression.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os, const ADQL::Nullif &nullif)
{
  return os << "NULLIF(" << nullif.arg0 << ',' << nullif.arg1 << ')';
}
}
