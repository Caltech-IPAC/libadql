#pragma once

#include "Numeric_Value_Expression/Operator_Numeric_Value_Expression.hxx"

namespace ADQL
{
class Numeric_Value_Expression
{
public:
  typedef boost::variant<Term, Operator_Numeric_Value_Expression> Variant;
  Variant variant;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Numeric_Value_Expression &numeric_value_expression)
{
  return os << numeric_value_expression.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Value_Expression,
                           (ADQL::Numeric_Value_Expression::Variant, variant))
