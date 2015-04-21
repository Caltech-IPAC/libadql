#pragma once

#include "Query_Specification_Wrap.hxx"
#include "Query_Specification/Search_Condition/Joined_Table.hxx"

namespace ADQL
{
class Subquery
{
public:
  typedef boost::variant<Joined_Table,Query_Specification_Wrap> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os, const Subquery &d)
{
  return os << '(' << d.variant << ')';
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Subquery,
                           (ADQL::Subquery::Variant, variant))
