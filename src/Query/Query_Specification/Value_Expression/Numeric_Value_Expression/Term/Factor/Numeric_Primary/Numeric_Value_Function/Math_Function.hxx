#pragma once

#include "Math_Function/Math_Zero_Arg.hxx"
#include "Math_Function/Math_One_Arg.hxx"
#include "Math_Function/Math_Two_Arg.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Math_Function
{
public:
  typedef boost::variant<Math_Zero_Arg, Math_One_Arg, Math_Two_Arg> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Math_Function &math_function)
{
  return os << math_function.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Math_Function,
                           (ADQL::Math_Function::Variant, variant))
