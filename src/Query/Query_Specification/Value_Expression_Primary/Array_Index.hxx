#pragma once

#include "../Numeric_Value_Expression.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Array_Index
{
public:
  Numeric_Value_Expression expression;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Array_Index &array_index)
{
  return os << '[' << array_index.expression << ']';
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Array_Index,
                           (ADQL::Numeric_Value_Expression, expression))
