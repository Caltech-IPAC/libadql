#include "../User_Defined_Function.hxx"
#include "../User_Defined_Function_Wrap.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::User_Defined_Function_Wrap &wrap)
{
  return os << wrap.get ();
}
}
