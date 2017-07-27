#include "../Numeric_Primary.hxx"
#include "../../../../Value_Expression_Primary.hxx"
#include "../../../../../empty_variant.hxx"

bool ADQL::Numeric_Primary::empty () const { return empty_variant (variant); }
