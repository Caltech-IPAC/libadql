#include "../Value_Expression_Non_Bool.hxx"
#include "../Value_Expression_Non_Bool_Wrap.hxx"

namespace ADQL {
bool empty(const Value_Expression_Non_Bool_Wrap &wrap) { return wrap.get().empty(); }
}  // namespace ADQL
