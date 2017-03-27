#pragma once

#include "../Search_Condition_Wrap.hxx"
#include "Boolean_Primary/Predicate.hxx"

namespace ADQL
{
class Boolean_Primary
{
public:
  typedef boost::variant<Predicate, Search_Condition_Wrap, std::string> Variant;
  Variant variant;
};
std::ostream &operator<<(std::ostream &os, const ADQL::Boolean_Primary &b);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Boolean_Primary,
                           (ADQL::Boolean_Primary::Variant, variant))
