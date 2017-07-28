#include "../Subquery_Wrap.hxx"
#include "../Subquery.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Subquery_Wrap &wrap)
{
  return os << wrap.get ();
}
}
