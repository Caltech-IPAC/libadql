#include "../../../../empty_variant.hxx"
#include "../../../Search_Condition.hxx"
#include "../../../Value_Expression_Non_Bool.hxx"
#include "../Boolean_Primary.hxx"

bool ADQL::Boolean_Primary::empty() const { return empty_variant(variant); }
