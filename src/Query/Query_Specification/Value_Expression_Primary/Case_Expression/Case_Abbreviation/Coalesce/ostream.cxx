#include "../../../../Value_Expression.hxx"
#include "../Coalesce.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Coalesce &coalesce) {
    os << "COALESCE(";
    for (auto c = coalesce.wraps.begin(); c != coalesce.wraps.end();) {
        os << *c;
        ++c;
        if (c != coalesce.wraps.end()) {
            os << ',';
        }
    }
    os << ')';
    return os;
}
}  // namespace ADQL
