#pragma once

#include "Set_Function_Specification/General_Set_Function.hxx"
#include "../../empty_variant.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Set_Function_Specification
{
public:
  typedef boost::variant<std::string, General_Set_Function> Variant;
  Variant variant;
  bool empty () const { return empty_variant (variant); }
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Set_Function_Specification &set_function_specification)
{
  return os << set_function_specification.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Set_Function_Specification,
                           (ADQL::Set_Function_Specification::Variant,
                            variant))
