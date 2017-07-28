#pragma once

#include "Search_Condition/Boolean_Term.hxx"
#include "../empty_variant.hxx"

namespace ADQL
{
class Search_Condition
{
public:
  typedef boost::variant<Boolean_Factor, Boolean_Term> Variant;
  Variant variant;

  bool empty () const { return empty_variant (variant); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Search_Condition &s)
{
  if (!s.empty ())
    {
      os << s.variant;
    }
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Search_Condition,
                           (ADQL::Search_Condition::Variant, variant))
