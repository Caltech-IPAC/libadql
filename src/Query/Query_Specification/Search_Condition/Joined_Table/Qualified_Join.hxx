#pragma once

#include "../../Join_Suffix.hxx"
#include "../../Table_Reference.hxx"

namespace ADQL
{
class Qualified_Join
{
public:
  Table_Correlation table_correlation;
  Join_Suffix join_suffix;
  bool empty () const
  {
    return table_correlation.empty ();
  }
};

inline std::ostream &operator<<(std::ostream &os, const Qualified_Join &j)
{
  return os << j.table_correlation << " " << j.join_suffix;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Qualified_Join,
                           (ADQL::Table_Correlation, table_correlation)
                           (ADQL::Join_Suffix, join_suffix))
