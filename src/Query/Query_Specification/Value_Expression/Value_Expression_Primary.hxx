#pragma once

#include "Value_Expression_Primary/Array_Constructor.hxx"
#include "Value_Expression_Primary/Set_Function_Specification.hxx"
#include "Value_Expression_Primary/Case_Expression.hxx"
#include "Value_Expression_Primary/Any_Expression.hxx"
#include "Value_Expression_Primary/Value_Subexpression.hxx"

namespace ADQL
{
class Value_Expression_Primary
{
public:
  std::string expression;
  std::vector<std::string> array_indices;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Value_Expression_Primary &value_expression_primary)
{
  os << value_expression_primary.expression;
  for (auto &index : value_expression_primary.array_indices)
    {
      os << '[' << index << ']';
    }
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression_Primary,
                           (std::string, expression)(std::vector<std::string>,
                                                     array_indices))
