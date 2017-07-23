#pragma once

#include "Value_Expression/Concatenation_Expression.hxx"
#include "Value_Expression/Numeric_Value_Expression.hxx"
#include "Value_Expression/String_Value_Expression.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Value_Expression
{
public:
  typedef boost::variant<Concatenation_Expression, Numeric_Value_Expression,
                         String_Value_Expression> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Value_Expression &value_expression)
{
  return os << value_expression.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression,
                           (ADQL::Value_Expression::Variant, variant))
