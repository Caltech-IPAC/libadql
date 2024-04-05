#pragma once

#include "Joined_Table.hxx"
#include "Select.hxx"
#include "Table_Reference.hxx"
#include "Table_Valued_Function.hxx"
#include "Where.hxx"

namespace ADQL {
class Select_From_Where {
public:
    Select select;
    std::vector<Table_Reference> tables;
    Where where;

    bool empty() const { return select.empty() || tables.empty(); }
};
}  // namespace ADQL

namespace ADQL {
inline std::ostream &operator<<(std::ostream &os,
                                const std::vector<Table_Reference> &tables) {
    const auto tables_end = tables.end();
    auto table_iter = tables.begin();
    if (table_iter != tables_end) {
        os << *table_iter;
        ++table_iter;
    }
    for (/* */; table_iter != tables_end; ++table_iter) {
        os << ", " << *table_iter;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Select_From_Where &select_from_where) {
    os << select_from_where.select << " FROM " << select_from_where.tables;
    if (!select_from_where.where.empty()) {
        os << " WHERE " << select_from_where.where;
    }
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Select_From_Where,
                          (ADQL::Select, select)(std::vector<ADQL::Table_Reference>,
                                                 tables)(ADQL::Where, where))
