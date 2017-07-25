#pragma once

#include "Searched_Case/Searched_When.hxx"
#include "../Result.hxx"

namespace ADQL
{
class Searched_Case
{
public:
  Searched_When when;
  Else_Clause else_clause;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Searched_Case &searched_case)
{
  os << "CASE " << searched_case.when;
  if (!searched_case.else_clause.empty ())
    {
      os << searched_case.else_clause;
    }
  os << "END ";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Searched_Case,
                           (ADQL::Searched_When, when)(ADQL::Else_Clause,
                                                       else_clause))
