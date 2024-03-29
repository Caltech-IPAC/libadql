#pragma once

#include "../empty_variant.hxx"
#include "Joined_Table/Qualified_Join.hxx"
#include "Joined_Table_Wrap.hxx"

namespace ADQL {
class Joined_Table {
public:
    typedef boost::variant<Qualified_Join, Joined_Table_Wrap> Variant;
    Variant variant;
    bool empty() const { return empty_variant(variant); }
};
std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table &j);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Joined_Table, (ADQL::Joined_Table::Variant, variant))
