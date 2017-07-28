#include "../Between_Predicate.hxx"
#include "../../../../../Value_Expression.hxx"
#include "../../../../../Value_Expression_Non_Bool.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os, const ADQL::Between_Predicate &b)
{
  return os << b.value << " " << b.Not << (b.Not.empty () ? "" : " ")
            << "BETWEEN " << b.low << " AND " << b.high;
}
}
