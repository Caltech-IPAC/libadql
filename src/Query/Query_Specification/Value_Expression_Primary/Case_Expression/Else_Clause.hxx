#pragma once

#include "Result.hxx"

namespace ADQL {
class Else_Clause {
public:
    Result result;
    bool empty() const { return result.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Else_Clause &else_clause) {
    return os << "ELSE " << else_clause.result;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Else_Clause, (ADQL::Result, result))
