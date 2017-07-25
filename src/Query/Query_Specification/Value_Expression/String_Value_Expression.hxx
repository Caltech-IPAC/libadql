#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class String_Value_Expression
{
public:
  std::string expression;
  bool empty () const { return expression.empty (); }
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::String_Value_Expression &string_value_expression)
{
  return os << string_value_expression.expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::String_Value_Expression,
                           (std::string, expression))
