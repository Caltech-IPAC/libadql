#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Numeric_Value_Expression
{
public:
  std::string term, plus_or_minus, expression;
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
                           (std::string, term)(std::string,
                                               plus_or_minus)(std::string,
                                                              expression))
