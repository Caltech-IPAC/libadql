#pragma once

#include "../Subquery.hxx"

namespace ADQL {
class With {
public:
    std::string table_name;
    std::vector<std::string> column_list;
    Subquery subquery;

    bool empty() const { return table_name.empty() && subquery.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::With &with) {
    os << "WITH " << with.table_name;
    if (!with.column_list.empty()) {
        os << " (";
        for (auto col_ptr = with.column_list.begin();
             col_ptr != with.column_list.end();) {
            os << *col_ptr;
            ++col_ptr;
            if (col_ptr != with.column_list.end()) {
                os << ",";
            }
        }
        os << ")";
    }
    os << " AS " << with.subquery;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::With,
                          (std::string, table_name)(std::vector<std::string>,
                                                    column_list)(ADQL::Subquery,
                                                                 subquery))
