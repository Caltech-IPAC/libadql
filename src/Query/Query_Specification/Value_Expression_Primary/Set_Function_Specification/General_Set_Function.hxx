#pragma once

#include "General_Set_Function/General_Set_Args.hxx"

namespace ADQL {
class General_Set_Function {
public:
    std::string set_function_type;
    General_Set_Args args;
    bool empty() const { return set_function_type.empty(); }
};

inline std::ostream &operator<<(
        std::ostream &os, const ADQL::General_Set_Function &general_set_function) {
    return os << general_set_function.set_function_type << '('
              << general_set_function.args << ')';
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::General_Set_Function,
                          (std::string, set_function_type)(ADQL::General_Set_Args,
                                                           args))
