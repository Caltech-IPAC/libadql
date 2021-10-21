#include "../../../../empty_variant.hxx"
#include "../../../User_Defined_Function.hxx"
#include "../Numeric_Value_Function.hxx"

bool ADQL::Numeric_Value_Function::empty() const { return empty_variant(variant); }
