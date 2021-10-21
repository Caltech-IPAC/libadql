#include "../../../../../../Subquery.hxx"
#include "../../../../../Value_Expression.hxx"
#include "../../../../../Value_Expression_Non_Bool.hxx"
#include "../../../../../ostream_vector.hxx"
#include "../In_Predicate.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::In_Predicate &p) {
    return os << p.value << " " << (p.Not.empty() ? "" : "NOT ") << "IN " << p.variant;
}
}  // namespace ADQL
