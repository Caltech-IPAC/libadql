#include "../../../Value_Expression.hxx"
#include "../Result.hxx"

bool ADQL::Result::empty() const { return empty_variant(variant); }
