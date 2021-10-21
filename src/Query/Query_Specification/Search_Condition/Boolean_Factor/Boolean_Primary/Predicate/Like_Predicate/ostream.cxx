#include "../../../../../Value_Expression.hxx"
#include "../../../../../Value_Expression_Non_Bool.hxx"
#include "../Like_Predicate.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Like_Predicate &c) {
    return os << c.match << (c.Not.empty() ? " " : " NOT ") << "LIKE " << c.pattern;
}
}  // namespace ADQL
