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
  std::string term;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Term &term)
{
  return os << term.term;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Term, (std::string, term))
