#include "../../empty_variant.hxx"
#include "../Group_By_Term.hxx"
#include "../Value_Expression.hxx"

bool ADQL::Group_By_Term::empty() const { return empty_variant(variant); }
