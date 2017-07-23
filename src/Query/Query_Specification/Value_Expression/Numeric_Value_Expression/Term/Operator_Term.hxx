#pragma once

#include "Term_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace ADQL
{
class Operator_Term
{
public:
  std::string factor, multiply_or_divide;
  Term_Wrap term;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Operator_Term &term)
{
  return os << term.factor << term.multiply_or_divide << term.term;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Operator_Term,
                           (std::string,
                            factor)(std::string,
                                    multiply_or_divide)(ADQL::Term_Wrap, term))
