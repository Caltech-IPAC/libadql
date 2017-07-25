#pragma once

#include "Numeric_Primary/Numeric_Value_Function.hxx"
#include "../../../Value_Expression_Primary_Wrap.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Numeric_Primary
{
public:
  typedef boost::variant<Value_Expression_Primary_Wrap, Numeric_Value_Function>
      Variant;
  Variant variant;
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Numeric_Primary &numeric_primary);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Primary,
                           (ADQL::Numeric_Primary::Variant, variant))
