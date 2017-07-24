#include "../Value_Expression_Primary.hxx"
#include "../Value_Expression_Primary_Wrap.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Value_Expression_Primary_Wrap &wrap)
{
  return os << wrap.get ();
}
}
