#include "../Value_Expression_Non_Bool_Wrap.hxx"
#include "../Value_Expression_Non_Bool.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Value_Expression_Non_Bool_Wrap &wrap)
{
  return os << wrap.get ();
}
}
