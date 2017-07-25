#pragma once

#include "Value_Expression_Primary/Array_Constructor.hxx"
#include "Value_Expression_Primary/Set_Function_Specification.hxx"
#include "Value_Expression_Primary/Case_Expression.hxx"
#include "Value_Expression_Primary/Any_Expression.hxx"

namespace ADQL
{
class Value_Expression_Primary
{
public:
  std::string expression;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Value_Expression_Primary &value_expression_primary)
{
  return os << value_expression_primary.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression_Primary,
                           (std::string, expression))
