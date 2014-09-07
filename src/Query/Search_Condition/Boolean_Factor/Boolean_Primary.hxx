#pragma once

#include "Boolean_Primary/Predicate.hxx"

namespace ADQL
{
typedef boost::variant<Predicate, Search_Condition_Wrap>
Boolean_Primary_Variant;

class Boolean_Primary
{
public:
  Boolean_Primary_Variant variant;
};

std::ostream &operator<<(std::ostream &os, const ADQL::Boolean_Primary &b);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Boolean_Primary,
                           (ADQL::Boolean_Primary_Variant, variant))
