#include "../Subquery_Wrap.hxx"
#include "../Subquery.hxx"

namespace ADQL
{
bool empty (const Subquery_Wrap &wrap)
{
  return wrap.get ().empty ();
}
}
