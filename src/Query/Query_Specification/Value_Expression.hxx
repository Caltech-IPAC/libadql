#pragma once

#include "Value_Expression/Numeric_Value_Expression.hxx"
#include "Value_Expression/String_Value_Expression.hxx"
#include "Value_Expression/Value_Expression_Primary.hxx"
#include "../empty_variant.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Value_Expression
{
public:
  typedef boost::variant<Numeric_Value_Expression, String_Value_Expression>
      Variant;
  Variant variant;
  bool empty () const { return empty_variant (variant); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Value_Expression &value_expression)
{
  return os << value_expression.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression,
                           (ADQL::Value_Expression::Variant, variant))
