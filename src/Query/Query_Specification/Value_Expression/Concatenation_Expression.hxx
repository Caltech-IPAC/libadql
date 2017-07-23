#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>


namespace ADQL
{
class Concatenation_Expression
{
public:
  std::string character_factor;
  std::string character_value_expression;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Concatenation_Expression &concatenation_expression)
{
  return os << concatenation_expression.character_factor << " || "
            << concatenation_expression.character_value_expression;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Concatenation_Expression,
                           (std::string,
                            character_factor)(std::string,
                                              character_value_expression))
