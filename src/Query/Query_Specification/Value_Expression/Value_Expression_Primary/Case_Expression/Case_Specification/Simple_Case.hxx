#pragma once

#include "Simple_Case/Simple_Whens.hxx"
#include "../Else_Clause.hxx"

namespace ADQL
{
class Simple_Case
{
public:
  std::string case_operand;
  Simple_Whens simple_whens;
  Else_Clause else_clause;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Simple_Case &simple_case)
{
  os << "CASE " << simple_case.simple_whens;
  if (!simple_case.else_clause.empty ())
    {
      os << simple_case.else_clause;
    }
  os << "END ";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Simple_Case,
                           (std::string,
                            case_operand)(ADQL::Simple_Whens,
                                          simple_whens)(ADQL::Else_Clause,
                                                        else_clause))
