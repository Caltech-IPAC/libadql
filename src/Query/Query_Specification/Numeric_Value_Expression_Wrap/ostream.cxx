#include "../Numeric_Value_Expression.hxx"
#include "../Numeric_Value_Expression_Wrap.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Numeric_Value_Expression_Wrap &wrap)
{
  return os << wrap.get ();
}
}
