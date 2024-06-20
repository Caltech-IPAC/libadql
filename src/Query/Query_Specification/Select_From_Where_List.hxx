#pragma once

#include <boost/algorithm/string.hpp>

#include "Select_From_Where.hxx"

namespace ADQL {

struct SFW_Addon {
    std::string union_op;
    Select_From_Where select_from_where;

    bool empty() { return union_op.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::SFW_Addon &sfw_addon) {
    os << " " << boost::to_upper_copy(sfw_addon.union_op) << " "
       << sfw_addon.select_from_where;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::SFW_Addon,
                          (std::string, union_op)(ADQL::Select_From_Where,
                                                  select_from_where))

namespace ADQL {

struct Select_From_Where_List {
    typedef std::vector<SFW_Addon> SFW_Addon_List;

    Select_From_Where select_from_where_initial;
    SFW_Addon_List select_from_where_addon_list;

    bool empty() const { return select_from_where_initial.empty(); }

    void validate_sfw_index(uint sfw_idx) const {
        if (sfw_idx >= get_num_sfws()) {
            throw std::runtime_error("sfw_idx must be less than " +
                                     to_string(get_num_sfws()));
        }
    }

    inline const Select_From_Where &get_initial_sfw() const {
        return select_from_where_initial;
    }

    inline const Select_From_Where &get_sfw(uint idx) const {
        if (idx == 0) {
            return select_from_where_initial;
        }
        validate_sfw_index(idx);
        return select_from_where_addon_list.at(idx - 1).select_from_where;
    }

    inline const std::string &get_union_op(uint union_idx) const {
        if (union_idx > 0 && union_idx < get_num_sfws()) {
            return select_from_where_addon_list.at(union_idx - 1).union_op;
        }
        throw std::runtime_error("union_idx must be >= 1 and <= " +
                                 to_string(get_num_sfws()));
    }

    inline uint get_num_sfws() const {
        if (empty()) {
            return 0;
        }
        return 1 + select_from_where_addon_list.size();
    }

    const Where &get_where(uint sfw_index) const {
        validate_sfw_index(sfw_index);
        return get_sfw(sfw_index).where;
    }

    const Select &get_select(uint sfw_index) const {
        validate_sfw_index(sfw_index);
        return get_sfw(sfw_index).select;
    }

    const Table_Reference &get_initial_table(uint sfw_index) const {
        validate_sfw_index(sfw_index);
        return get_sfw(sfw_index).tables.at(0);
    }

    // JTODO set, not vector?  Would have to define sort.
    const std::vector<Table_Reference> get_combined_table_list() const {
        std::vector<Table_Reference> table_list;
        if (empty()) {
            return table_list;
        }
        uint num_sfws = get_num_sfws();
        for (uint i = 0; i < num_sfws; ++i) {
            const auto &sfw = get_sfw(i);
            table_list.insert(table_list.end(), sfw.tables.begin(), sfw.tables.end());
        }
        return table_list;
    }

    const std::vector<std::vector<Table_Reference>> get_table_lists_by_sfw() const {
        std::vector<std::vector<Table_Reference>> table_lists;
        uint num_sfws = get_num_sfws();

        if (num_sfws == 0) {
            return table_lists;
        }

        for (uint i = 0; i < num_sfws; ++i) {
            const auto &sfw = get_sfw(i);
            table_lists.emplace_back(sfw.tables);
        }
        return table_lists;
    }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Select_From_Where_List &sfw_list) {
    os << sfw_list.select_from_where_initial;

    const auto &sfw_addons = sfw_list.select_from_where_addon_list;
    for (const auto &sfw_pair : sfw_addons) {
        os << sfw_pair;
    }
    return os;
}

}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Select_From_Where_List,
                          (ADQL::Select_From_Where, select_from_where_initial)(
                                  ADQL::Select_From_Where_List::SFW_Addon_List,
                                  select_from_where_addon_list))
