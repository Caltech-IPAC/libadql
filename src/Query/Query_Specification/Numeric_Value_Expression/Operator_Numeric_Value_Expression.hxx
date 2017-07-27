#pragma once

#include "../Numeric_Value_Expression_Wrap.hxx"
#include "Term.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace ADQL
{
class Operator_Numeric_Value_Expression
{
public:
  Term term;
  std::string plus_or_minus;
  Numeric_Value_Expression_Wrap wrap;
  bool empty () const { return plus_or_minus.empty (); }
};

inline std::ostream &
operator<<(std::ostream &os, const ADQL::Operator_Numeric_Value_Expression &op)
{
  return os << op.term << op.plus_or_minus << op.wrap;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Operator_Numeric_Value_Expression,
                           (ADQL::Term, term)(std::string, plus_or_minus)(
                               ADQL::Numeric_Value_Expression_Wrap, wrap))
