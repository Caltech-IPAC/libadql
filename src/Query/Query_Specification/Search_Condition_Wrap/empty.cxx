#include "../Search_Condition.hxx"
#include "../Search_Condition_Wrap.hxx"

namespace ADQL {
bool empty(const Search_Condition_Wrap &s) { return s.get().empty(); }
}  // namespace ADQL
