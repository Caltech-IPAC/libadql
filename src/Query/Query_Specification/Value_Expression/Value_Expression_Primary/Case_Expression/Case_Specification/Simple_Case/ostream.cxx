#include "../Simple_Case.hxx"
#include "../../../../../Value_Expression.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Simple_Case &simple_case)
{
  os << "CASE " << simple_case.case_operand << " " << simple_case.simple_whens;
  if (!simple_case.else_clause.empty ())
    {
      os << simple_case.else_clause;
    }
  os << "END";
  return os;
}
}
