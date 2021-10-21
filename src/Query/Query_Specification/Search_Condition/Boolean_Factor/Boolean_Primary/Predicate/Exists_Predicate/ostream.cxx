#include "../../../../../../Subquery.hxx"
#include "../Exists_Predicate.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Exists_Predicate &c) {
    return os << "EXISTS " << c.subquery;
}
}  // namespace ADQL
