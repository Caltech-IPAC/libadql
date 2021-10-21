#include "../../../../Value_Expression.hxx"
#include "../Nullif.hxx"

namespace ADQL {
bool Nullif::empty() const { return ADQL::empty(arg0); }
}  // namespace ADQL
