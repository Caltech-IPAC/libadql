#include "../Table_Reference_Wrap.hxx"
#include "../Table_Reference.hxx"

#include <iostream>

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Table_Reference_Wrap &wrap)
{
  return os << wrap.get ();
}
}
