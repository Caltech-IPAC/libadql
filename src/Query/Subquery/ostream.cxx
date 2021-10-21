#include <iostream>
#include "../Query_Specification.hxx"
#include "../Subquery.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Subquery &subquery) {
    return os << '(' << subquery.variant << ')';
}
}  // namespace ADQL
