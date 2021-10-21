#pragma once

#include "Value_Expression_Non_Bool_Term.hxx"

namespace ADQL {
class Value_Expression_Non_Bool {
public:
    Factor factor;
    std::vector<Value_Expression_Non_Bool_Term> terms;
    bool empty() const { return factor.empty(); }
};

inline std::ostream &operator<<(
        std::ostream &os,
        const ADQL::Value_Expression_Non_Bool &value_expression_non_bool) {
    os << value_expression_non_bool.factor;
    for (auto &term : value_expression_non_bool.terms) {
        os << term;
    }
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Value_Expression_Non_Bool,
                          (ADQL::Factor,
                           factor)(std::vector<ADQL::Value_Expression_Non_Bool_Term>,
                                   terms))
