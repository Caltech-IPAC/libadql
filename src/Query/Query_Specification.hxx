#pragma once

#include "Query_Specification/Group_By.hxx"
#include "Query_Specification/Having.hxx"
#include "Query_Specification/Joined_Table.hxx"
#include "Query_Specification/Order_By.hxx"
#include "Query_Specification/Select_From_Where.hxx"
#include "Query_Specification/Select_From_Where_List.hxx"
#include "Query_Specification/With.hxx"

namespace ADQL {
class Query_Specification {
public:
    With with;
    Select_From_Where_List select_from_where_list;
    Group_By group_by;
    Order_By order_by;
    Having having;

    bool empty() const {
        // I think that it is an error for a query to be empty.
        return select_from_where_list.empty();
    }

    inline void validate_sfw_index(uint idx) const {
        select_from_where_list.validate_sfw_index(idx);
    }

    inline const Select_From_Where &get_initial_sfw() const {
        return select_from_where_list.get_initial_sfw();
    }

    inline const Select_From_Where &get_sfw(uint idx) const {
        return select_from_where_list.get_sfw(idx);
    }

    inline const std::string &get_union_op(uint idx) const {
        return select_from_where_list.get_union_op(idx);
    }

    uint get_num_union_components() const {
        return select_from_where_list.get_num_sfws();
    }

    bool is_union_query() const { return (get_num_union_components() > 1); }

    const Where &get_where(uint sfw_idx) const {
        return select_from_where_list.get_where(sfw_idx);
    }

    const Select &get_select(uint sfw_idx) const {
        validate_sfw_index(sfw_idx);
        return select_from_where_list.get_select(sfw_idx);
    }

    Select &get_select(uint sfw_idx) {
        validate_sfw_index(sfw_idx);
        return select_from_where_list.get_select(sfw_idx);
    }

    const Table_Reference &get_initial_table(uint sfw_idx) const {
        validate_sfw_index(sfw_idx);
        return select_from_where_list.get_initial_table(sfw_idx);
    }

    const std::vector<Table_Reference> get_combined_table_list() const {
        return select_from_where_list.get_combined_table_list();
    }

    const std::vector<std::vector<Table_Reference>> get_table_lists_by_sfw() const {
        return select_from_where_list.get_table_lists_by_sfw();
    }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Query_Specification &query) {
    if (!query.with.empty()) {
        os << query.with << " ";
    }

    os << query.select_from_where_list;

    if (!query.group_by.empty()) os << " GROUP BY " << query.group_by;
    if (!query.having.empty()) os << " HAVING " << query.having;
    if (!query.order_by.empty()) os << " ORDER BY " << query.order_by;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Query_Specification,
                          (ADQL::With, with)(ADQL::Select_From_Where_List,
                                             select_from_where_list)(ADQL::Group_By,
                                                                     group_by)(
                                  ADQL::Having, having)(ADQL::Order_By, order_by))
