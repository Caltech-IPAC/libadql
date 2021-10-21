#include "../../empty_variant.hxx"
#include "../Table_Reference.hxx"

namespace ADQL {
bool Table_Reference::empty() const { return empty_variant(variant); }
}  // namespace ADQL
