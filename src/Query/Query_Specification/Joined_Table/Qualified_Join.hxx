#pragma once

#include "../Join_Suffix.hxx"
#include "../Table_Reference.hxx"
#include "../Joined_Table_Wrap.hxx"
#include "../../empty_variant.hxx"

namespace ADQL
{
class Qualified_Join
{
public:
  typedef boost::variant<Table_Correlation, Joined_Table_Wrap> Variant;
  Variant variant;
  std::vector<Join_Suffix> join_suffixes;
  bool empty () const
  {
    return empty_variant (variant);
  }
};
std::ostream &operator<<(std::ostream &os, const ADQL::Qualified_Join &j);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Qualified_Join,
                           (ADQL::Qualified_Join::Variant, variant)
                           (std::vector<ADQL::Join_Suffix>, join_suffixes))
