#include <iostream>
#include "../Subquery.hxx"
#include "../Query_Specification.hxx"

namespace ADQL
{
  std::ostream &operator<<(std::ostream &os, const ADQL::Subquery &subquery)
  {
    return os << '(' << subquery.variant << ')';
  }
}
