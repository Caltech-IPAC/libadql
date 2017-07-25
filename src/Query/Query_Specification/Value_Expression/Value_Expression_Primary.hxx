#pragma once

#include "Value_Expression_Primary/Array_Constructor.hxx"
#include "Value_Expression_Primary/Set_Function_Specification.hxx"
#include "Value_Expression_Primary/Case_Expression.hxx"
#include "Value_Expression_Primary/Any_Expression.hxx"
#include "Value_Expression_Primary/Value_Subexpression.hxx"
#include "Value_Expression_Primary/Array_Index.hxx"
#include "../Column_Reference.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Value_Expression_Primary
{
public:
  typedef boost::variant<Array_Constructor, std::string, Column_Reference,
                         Set_Function_Specification, Case_Expression,
                         Any_Expression, Value_Subexpression> Variant;
  Variant variant;
  std::vector<Array_Index> array_indices;
};

std::ostream &
operator<<(std::ostream &os,
           const ADQL::Value_Expression_Primary &value_expression_primary);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression_Primary,
                           (ADQL::Value_Expression_Primary::Variant,
                            variant)(std::vector<ADQL::Array_Index>,
                                     array_indices))
