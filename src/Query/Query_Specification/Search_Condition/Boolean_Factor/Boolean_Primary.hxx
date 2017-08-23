#pragma once

#include "../../Search_Condition_Wrap.hxx"
#include "Boolean_Primary/Predicate.hxx"
#include "../../Value_Expression_Non_Bool_Wrap.hxx"

namespace ADQL
{
class Boolean_Primary
{
public:
  typedef boost::variant<Predicate, Search_Condition_Wrap,
                         Value_Expression_Non_Bool_Wrap> Variant;
  Variant variant;
  bool empty () const;
};
std::ostream &operator<<(std::ostream &os, const ADQL::Boolean_Primary &b);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Boolean_Primary,
                           (ADQL::Boolean_Primary::Variant, variant))
