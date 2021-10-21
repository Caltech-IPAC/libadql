#include "../Value_Expression_Primary.hxx"

namespace ADQL {
std::ostream &operator<<(
        std::ostream &os,
        const ADQL::Value_Expression_Primary &value_expression_primary) {
    os << value_expression_primary.variant;
    for (auto &index : value_expression_primary.array_indices) {
        os << index;
    }
    return os;
}
}  // namespace ADQL
