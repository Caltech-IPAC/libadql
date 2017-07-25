#include "../Table_Reference.hxx"
#include "../../empty_variant.hxx"

namespace ADQL
{
bool Table_Reference::empty () const { return empty_variant (variant); }
}
