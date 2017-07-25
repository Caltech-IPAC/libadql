#pragma once

#include "Case_Specification/Simple_Case.hxx"
#include "Case_Specification/Searched_Case.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Case_Specification
{
public:
  typedef boost::variant<Simple_Case, Searched_Case> Variant;
  Variant variant;
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Case_Specification &case_specification)
{
  return os << case_specification.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Case_Specification,
                           (ADQL::Case_Specification::Variant, variant))
