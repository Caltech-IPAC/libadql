#pragma once

#include "Join_Specification/Join_Condition.hxx"

namespace ADQL
{
class Join_Specification
{
public:
  typedef boost::variant<Join_Condition, std::string> Variant;
  Variant variant;
  bool empty () const { return variant.empty (); }
};
inline std::ostream &operator<<(std::ostream &os, const Join_Specification &j)
{
  return os << j.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Join_Specification,
                           (ADQL::Join_Specification::Variant, variant))
