#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

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
