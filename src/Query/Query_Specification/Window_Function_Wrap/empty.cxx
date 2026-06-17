#include "../Window_Function.hxx"
#include "../Window_Function_Wrap.hxx"

namespace ADQL {
bool empty(const Window_Function_Wrap &s) { return s.get().empty(); }
}  // namespace ADQL
