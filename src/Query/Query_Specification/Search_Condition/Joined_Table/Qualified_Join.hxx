#pragma once

#include "../../Join_Suffix.hxx"
#include "../../Table_Reference.hxx"

namespace ADQL
{
class Qualified_Join
{
public:
  Table_Correlation table_correlation;
  // Table_Reference table_reference;
  Join_Suffix join_suffix;
  bool empty () const
  {
    return table_correlation.empty ();
    // return table_reference.empty ();
  }
};

inline std::ostream &operator<<(std::ostream &os, const Qualified_Join &j)
{
  return os << j.table_correlation << " " << j.join_suffix;
  // return os << j.table_reference << " " << j.join_suffix;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Qualified_Join,
                           (ADQL::Table_Correlation, table_correlation)
                           // (ADQL::Table_Reference, table_reference)
                           (ADQL::Join_Suffix, join_suffix))
