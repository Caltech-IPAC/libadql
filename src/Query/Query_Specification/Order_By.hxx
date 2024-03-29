#pragma once

#include "Order_By/Sort_Specification.hxx"

#include <vector>

namespace ADQL {
class Order_By {
public:
    std::vector<Sort_Specification> sort_specifications;
    bool empty() const { return sort_specifications.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Order_By &order_by) {
    for (auto r = order_by.sort_specifications.begin();
         r != order_by.sort_specifications.end();) {
        os << *r;
        ++r;
        if (r != order_by.sort_specifications.end()) {
            os << ",";
        }
    }
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Order_By,
                          (std::vector<ADQL::Sort_Specification>, sort_specifications))
