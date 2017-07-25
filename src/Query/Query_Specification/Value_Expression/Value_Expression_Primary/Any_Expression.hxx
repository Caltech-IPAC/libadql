#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Any_Expression
{
public:
  std::string expression;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Any_Expression &any_expression)
{
  return os << any_expression.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Any_Expression, (std::string, expression))
