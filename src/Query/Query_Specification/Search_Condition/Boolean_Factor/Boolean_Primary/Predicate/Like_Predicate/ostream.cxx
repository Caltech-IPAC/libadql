#include "../Like_Predicate.hxx"
#include "../../../../../String_Value_Expression.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                                const ADQL::Like_Predicate &c)
{
  return os << c.match << (c.Not.empty () ? " " : "NOT ") << "LIKE "
            << c.pattern;
}
}
