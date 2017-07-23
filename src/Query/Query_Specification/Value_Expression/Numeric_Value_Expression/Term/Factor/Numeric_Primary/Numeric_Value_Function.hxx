#pragma once

#include "Numeric_Value_Function/Trig_Function.hxx"
#include "Numeric_Value_Function/Math_Function.hxx"
#include "Numeric_Value_Function/Cast_Function.hxx"
#include "../../../../../User_Defined_Function.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Numeric_Value_Function
{
public:
  // FIXME: Use User_Defined_Function_Wrap
  typedef boost::variant<Trig_Function, Math_Function, Cast_Function,
                         User_Defined_Function> Variant;
  Variant variant;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Numeric_Value_Function &numeric_value_function)
{
  return os << numeric_value_function.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Value_Function,
                           (ADQL::Numeric_Value_Function::Variant, variant))
