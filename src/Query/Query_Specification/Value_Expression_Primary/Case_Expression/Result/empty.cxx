#include "../Result.hxx"
#include "../../../Value_Expression.hxx"

bool ADQL::Result::empty () const { return empty_variant (variant); }
