#include "../Query_Specification.hxx"
#include "../Subquery.hxx"
#include "../empty_variant.hxx"

bool ADQL::Subquery::empty() const { return empty_variant(variant); }
