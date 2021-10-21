#include "../../../../Value_Expression.hxx"
#include "../Nullif.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Nullif &nullif) {
    return os << "NULLIF(" << nullif.arg0 << ',' << nullif.arg1 << ')';
}
}  // namespace ADQL
