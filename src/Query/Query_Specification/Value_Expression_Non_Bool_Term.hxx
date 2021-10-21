#pragma once

#include "Factor.hxx"

namespace ADQL {
class Value_Expression_Non_Bool_Term {
public:
    std::string operator_string;
    Factor factor;
    bool empty() const { return operator_string.empty(); }
};

inline std::ostream &operator<<(
        std::ostream &os,
        const ADQL::Value_Expression_Non_Bool_Term &value_expression_non_bool_term) {
    return os << value_expression_non_bool_term.operator_string
              << value_expression_non_bool_term.factor;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Value_Expression_Non_Bool_Term,
                          (std::string, operator_string)(ADQL::Factor, factor))
