#pragma once

#include "../Column_Reference.hxx"
#include "../User_Defined_Function.hxx"

namespace ADQL {
typedef boost::variant<std::string, Column_Reference, User_Defined_Function> Sort_Key;
}
