#pragma once

#include "Simple_Case/Simple_Whens.hxx"
#include "../Else_Clause.hxx"
#include "../../../Value_Expression_Wrap.hxx"

namespace ADQL
{
class Simple_Case
{
public:
  Value_Expression_Wrap case_operand;
  Simple_Whens simple_whens;
  Else_Clause else_clause;
  bool empty () const { return ADQL::empty (case_operand); }
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Simple_Case &simple_case);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Simple_Case,
                           (ADQL::Value_Expression_Wrap,
                            case_operand)(ADQL::Simple_Whens,
                                          simple_whens)(ADQL::Else_Clause,
                                                        else_clause))
