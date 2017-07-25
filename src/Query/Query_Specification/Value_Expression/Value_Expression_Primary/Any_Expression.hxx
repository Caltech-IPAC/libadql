#pragma once

#include "../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Any_Expression
{
public:
  Value_Expression_Wrap wrap;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Any_Expression &any_expression)
{
  return os << "ANY(" << any_expression.wrap << ')';
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Any_Expression,
                           (ADQL::Value_Expression_Wrap, wrap))
