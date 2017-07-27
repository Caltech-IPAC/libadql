#include "../Nullif.hxx"
#include "../../../../Value_Expression.hxx"

namespace ADQL
{
bool Nullif::empty () const { return ADQL::empty (arg0); }
}
