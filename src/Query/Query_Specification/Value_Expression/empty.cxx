#include "../../empty_variant.hxx"
#include "../Search_Condition.hxx"
#include "../Value_Expression.hxx"

bool ADQL::Value_Expression::empty() const { return empty_variant(variant); }
