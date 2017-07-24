#pragma once

#include "Trig_Function/Trig_One_Arg.hxx"
#include "Trig_Function/Trig_Two_Arg.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Trig_Function
{
public:
  typedef boost::variant<Trig_One_Arg, Trig_Two_Arg> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Trig_Function &trig_function)
{
  return os << trig_function.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Trig_Function,
                           (ADQL::Trig_Function::Variant, variant))
