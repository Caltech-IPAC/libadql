#include "../Exists_Predicate.hxx"
#include "../../../../../../Subquery.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Exists_Predicate &c)
{
  return os << "EXISTS " << c.subquery;
}
}
