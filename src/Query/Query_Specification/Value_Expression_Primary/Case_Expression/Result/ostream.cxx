#include "../../../Value_Expression.hxx"
#include "../Result.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Result &result) {
    return os << result.variant;
}
}  // namespace ADQL
