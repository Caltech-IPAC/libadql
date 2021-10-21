#pragma once

#include "../Else_Clause.hxx"
#include "../Result.hxx"
#include "Searched_Case/Searched_Whens.hxx"

namespace ADQL {
class Searched_Case {
public:
    Searched_Whens whens;
    Else_Clause else_clause;
    bool empty() const { return whens.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Searched_Case &searched_case) {
    os << "CASE " << searched_case.whens;
    if (!searched_case.else_clause.empty()) {
        os << searched_case.else_clause << " ";
    }
    os << "END";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Searched_Case,
                          (ADQL::Searched_Whens, whens)(ADQL::Else_Clause, else_clause))
