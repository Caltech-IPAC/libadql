#include "../../../empty_variant.hxx"
#include "../../Value_Expression_Primary.hxx"
#include "../Numeric_Primary.hxx"

bool ADQL::Numeric_Primary::empty() const { return empty_variant(variant); }
