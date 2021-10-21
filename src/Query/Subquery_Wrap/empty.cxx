#include "../Subquery.hxx"
#include "../Subquery_Wrap.hxx"

namespace ADQL {
bool empty(const Subquery_Wrap &wrap) { return wrap.get().empty(); }
}  // namespace ADQL
