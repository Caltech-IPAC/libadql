#pragma once

#include "Numeric_Value_Expression/Term.hxx"

namespace ADQL
{
class Numeric_Value_Expression
{
public:
  Term term;
  std::string plus_or_minus, expression;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Numeric_Value_Expression &numeric_value_expression)
{
  return os << numeric_value_expression.term
            << numeric_value_expression.plus_or_minus
            << numeric_value_expression.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Value_Expression,
                           (ADQL::Term, term)(std::string,
                                              plus_or_minus)(std::string,
                                                             expression))
