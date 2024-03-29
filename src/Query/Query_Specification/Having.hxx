#pragma once

#include "Search_Condition.hxx"

namespace ADQL {
class Having {
public:
    Search_Condition search_condition;
    bool empty() const { return search_condition.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Having &having) {
    return os << having.search_condition;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Having, (ADQL::Search_Condition, search_condition))
