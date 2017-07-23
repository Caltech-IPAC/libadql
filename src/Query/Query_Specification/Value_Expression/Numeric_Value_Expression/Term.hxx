#pragma once

#include "Term/Operator_Term.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Term
{
public:
  typedef boost::variant<Factor, Operator_Term> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Term &term)
{
  return os << term.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Term, (ADQL::Term::Variant, variant))
