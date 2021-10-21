#pragma once

#include "Column_Reference.hxx"
#include "Value_Expression_Wrap.hxx"

namespace ADQL {
class Group_By_Term {
public:
    typedef boost::variant<Column_Reference, Value_Expression_Wrap> Variant;
    Variant variant;
    bool empty() const;
};

std::ostream &operator<<(std::ostream &os, const ADQL::Group_By_Term &group_by_term);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Group_By_Term, (ADQL::Group_By_Term::Variant, variant))
