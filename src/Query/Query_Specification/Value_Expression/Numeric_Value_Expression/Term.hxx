#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Term
{
public:
  std::string factor, multiply_or_divide, term;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Term &term)
{
  return os << term.factor << term.multiply_or_divide << term.term;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Term,
                           (std::string,
                            factor)(std::string,
                                    multiply_or_divide)(std::string, term))
