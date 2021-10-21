#pragma once

#include "Join_Suffix/Join_Specification.hxx"
#include "Join_Suffix/Outer_Join.hxx"
#include "Table_Reference_Wrap.hxx"

namespace ADQL {
class Join_Suffix {
public:
    bool natural = false;
    typedef boost::variant<std::string, Outer_Join> Join_Type;
    Join_Type join_type;
    Table_Reference_Wrap table_reference_wrap;
    Join_Specification join_specification;
    bool empty() const { return ADQL::empty(table_reference_wrap); }
};

inline std::ostream &operator<<(std::ostream &os, const Join_Suffix &j) {
    if (j.natural) os << "NATURAL ";
    if (!j.join_type.empty()) os << j.join_type << " ";
    os << "JOIN " << j.table_reference_wrap;
    if (!j.join_specification.empty()) os << " " << j.join_specification;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Join_Suffix,
                          (bool, natural)(ADQL::Join_Suffix::Join_Type, join_type)(
                                  ADQL::Table_Reference_Wrap,
                                  table_reference_wrap)(ADQL::Join_Specification,
                                                        join_specification))
