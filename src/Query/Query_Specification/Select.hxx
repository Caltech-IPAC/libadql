#pragma once

#include "As.hxx"
#include "Non_As.hxx"
#include "Table_Valued_Function.hxx"
#include "User_Defined_Function.hxx"
#include "Value_Expression_Primary.hxx"

namespace ADQL {
class Select {
public:
    typedef boost::variant<As, Non_As> Column_Variant;
    typedef boost::variant<std::string, std::vector<Column_Variant> > Columns;

    Columns columns;
    std::string all_or_distinct;
    size_t top = std::numeric_limits<size_t>::max();

    bool empty() const { return columns.empty(); }
};
}  // namespace ADQL

namespace {
class Select_Columns_Visitor : public boost::static_visitor<std::ostream &> {
public:
    std::ostream &os;
    Select_Columns_Visitor(std::ostream &OS) : os(OS) {}
    Select_Columns_Visitor() = delete;

    std::ostream &operator()(const std::string &s) const { return os << s; }

    std::ostream &operator()(
            const std::vector<ADQL::Select::Column_Variant> &cols) const {
        const auto cols_end = cols.end();
        auto cols_iter = cols.begin();
        if (cols_iter != cols_end) {
            os << *cols_iter;
            ++cols_iter;
        }
        for (/* */; cols_iter != cols_end; ++cols_iter) {
            os << ", " << *cols_iter;
        }
        return os;
    }
};
}  // namespace

namespace ADQL {

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Select::Columns &columns) {
    return boost::apply_visitor(Select_Columns_Visitor(os), columns);
}

inline std::ostream &operator<<(std::ostream &os, const ADQL::Select &select) {
    os << "SELECT " << select.all_or_distinct
       << (select.all_or_distinct.empty() ? "" : " ")
       << (select.top != std::numeric_limits<unsigned long long>::max()
                   ? "TOP " + std::to_string(select.top) + " "
                   : "")
       << select.columns;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Select, (std::string, all_or_distinct)(size_t, top)(
                                                ADQL::Select::Columns, columns))
