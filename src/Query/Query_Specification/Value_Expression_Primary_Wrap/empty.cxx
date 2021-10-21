#include "../Value_Expression_Primary.hxx"
#include "../Value_Expression_Primary_Wrap.hxx"

namespace ADQL {
bool empty(const Value_Expression_Primary_Wrap &wrap) { return wrap.get().empty(); }
}  // namespace ADQL
