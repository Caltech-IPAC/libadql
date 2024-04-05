#pragma once

#include "Query_Specification/Group_By.hxx"
#include "Query_Specification/Having.hxx"
#include "Query_Specification/Joined_Table.hxx"
#include "Query_Specification/Order_By.hxx"
#include "Query_Specification/Select_From_Where.hxx"
#include "Query_Specification/With.hxx"

namespace ADQL {
class Query_Specification {
public:
    typedef std::vector<Select_From_Where> Select_From_Where_List;

    With with;
    Select_From_Where_List select_from_where_list;
    Group_By group_by;
    Order_By order_by;
    Having having;

    bool empty() const {
        // I think that it is an error for a query to be empty.
        return (select_from_where_list.empty() || select_from_where_list.at(0).empty());
    }

    uint get_num_union_components() const { return select_from_where_list.size(); }

    const std::vector<Table_Reference> get_combined_table_list() const {
        if (select_from_where_list.size() == 1) {
            return select_from_where_list.at(0).tables;
        }

        std::vector<Table_Reference> table_list;
        for (const auto &sfw : select_from_where_list) {
            table_list.insert(table_list.end(), sfw.tables.begin(), sfw.tables.end());
        }
        return table_list;
    }

    const Where &get_where(uint sfw_index) const {
        if (sfw_index < select_from_where_list.size()) {
            return select_from_where_list.at(sfw_index).where;
        }
        throw std::runtime_error("sfw_index must be less than " +
                                 to_string(select_from_where_list.size()));
    }

    const Select &get_select(uint sfw_index) const {
        if (sfw_index < select_from_where_list.size()) {
            return select_from_where_list.at(sfw_index).select;
        }
        throw std::runtime_error("sfw_index must be less than " +
                                 to_string(select_from_where_list.size()));
    }

    const Table_Reference &get_initial_table(uint sfw_index) const {
        if (sfw_index < select_from_where_list.size()) {
            return select_from_where_list.at(sfw_index).tables.at(0);
        }
        throw std::runtime_error("sfw_index must be less than " +
                                 to_string(select_from_where_list.size()));
    }

    bool is_union_query() const { return (select_from_where_list.size() > 1); }

    std::vector<std::vector<Table_Reference>> get_table_lists_by_sfw() const {
        std::vector<std::vector<Table_Reference>> table_lists;
        for (const auto &sfw : select_from_where_list) {
            table_lists.emplace_back(sfw.tables);
        }
        return table_lists;
    }
};
}  // namespace ADQL

namespace ADQL {

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Query_Specification &query) {
    if (!query.with.empty()) {
        os << query.with << " ";
    }

    const auto sfw_end = query.select_from_where_list.end();
    for (auto sfw_iter = query.select_from_where_list.begin(); sfw_iter != sfw_end;
         /* */) {
        os << *sfw_iter;
        ++sfw_iter;
        if (sfw_iter != sfw_end) {
            os << " UNION ";
        }
    }

    if (!query.group_by.empty()) os << " GROUP BY " << query.group_by;
    if (!query.having.empty()) os << " HAVING " << query.having;
    if (!query.order_by.empty()) os << " ORDER BY " << query.order_by;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Query_Specification,
                          (ADQL::With,
                           with)(ADQL::Query_Specification::Select_From_Where_List,
                                 select_from_where_list)(ADQL::Group_By, group_by)(
                                  ADQL::Having, having)(ADQL::Order_By, order_by))
