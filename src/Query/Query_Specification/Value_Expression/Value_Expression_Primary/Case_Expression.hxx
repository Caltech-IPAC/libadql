#pragma once

#include "Case_Expression/Case_Abbreviation.hxx"
#include "Case_Expression/Case_Specification.hxx"

namespace ADQL
{
class Case_Expression
{
public:
  typedef boost::variant<Case_Abbreviation, Case_Specification> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Case_Expression &case_expression)
{
  return os << case_expression.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Case_Expression, (ADQL::Case_Expression::Variant, variant))
