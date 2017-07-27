#include "../Simple_When.hxx"
#include "../../../../../../Value_Expression.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                                const ADQL::Simple_When &simple_when)
{
  return os << "WHEN " << simple_when.wrap << " "
            << "THEN " << simple_when.result;
}
}
