#pragma once

#include "Numeric_Value_Function/Trig_Function.hxx"
#include "Numeric_Value_Function/Math_Function.hxx"
#include "Numeric_Value_Function/Cast_Function.hxx"
#include "../../User_Defined_Function_Wrap.hxx"
#include "../../Non_Predicate_Geometry_Function.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Numeric_Value_Function
{
public:
  typedef boost::variant<Trig_Function, Math_Function, Cast_Function,
                         Non_Predicate_Geometry_Function,
                         User_Defined_Function_Wrap> Variant;
  Variant variant;
  bool empty () const;
};

std::ostream &
operator<<(std::ostream &os,
           const ADQL::Numeric_Value_Function &numeric_value_function);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Value_Function,
                           (ADQL::Numeric_Value_Function::Variant, variant))
