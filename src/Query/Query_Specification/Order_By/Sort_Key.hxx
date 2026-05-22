#pragma once

#include "../Column_Reference.hxx"
#include "../Value_Expression_Primary/Case_Expression.hxx"
#include "../Whitelisted_Function.hxx"

namespace ADQL {
typedef boost::variant<std::string, Column_Reference, Whitelisted_Function,
                       Case_Expression>
        Sort_Key;
}
