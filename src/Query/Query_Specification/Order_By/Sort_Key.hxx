#pragma once

#include "../Column_Reference.hxx"
#include "../User_Defined_Function.hxx"
#include "../Value_Expression_Primary/Case_Expression.hxx"

namespace ADQL {
  typedef boost::variant<std::string, Column_Reference, User_Defined_Function, Case_Expression> Sort_Key;
}
