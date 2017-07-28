#include "../Value_Expression.hxx"
#include "../Search_Condition.hxx"
#include "../../empty_variant.hxx"

bool ADQL::Value_Expression::empty () const { return empty_variant (variant); }
