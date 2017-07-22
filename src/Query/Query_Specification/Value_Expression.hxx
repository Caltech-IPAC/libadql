#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Value_Expression
{
public:
  std::string expression;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Value_Expression &value_expression)
{
  return os << value_expression.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression,
                           (std::string, expression))
