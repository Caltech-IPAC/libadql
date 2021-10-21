#include "../Group_By_Term.hxx"
#include "../Value_Expression.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Group_By_Term &group_by_term) {
    return os << group_by_term.variant;
}
}  // namespace ADQL
