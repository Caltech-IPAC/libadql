#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Case_Expression
{
public:
  std::string expression;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Case_Expression &case_expression)
{
  return os << case_expression.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Case_Expression, (std::string, expression))
