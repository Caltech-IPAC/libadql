#include "../../Term.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os, const ADQL::Term_Wrap &term_wrap)
{
  return os << term_wrap.get ();
}
}
