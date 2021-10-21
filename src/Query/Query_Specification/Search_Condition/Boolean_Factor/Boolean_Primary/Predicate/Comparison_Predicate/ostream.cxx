#include "../../../../../Value_Expression.hxx"
#include "../../../../../Value_Expression_Non_Bool.hxx"
#include "../Comparison_Predicate.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Comparison_Predicate &c) {
    return os << c.left << " " << c.op << " " << c.right;
}
}  // namespace ADQL
