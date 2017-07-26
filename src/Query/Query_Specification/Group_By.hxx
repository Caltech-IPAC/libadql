#pragma once

#include "Column_Reference.hxx"

#include <vector>

namespace ADQL
{
class Group_By
{
public:
  std::vector<Column_Reference> references;
  bool empty () const { return references.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Group_By &group_by)
{
  for (auto r=group_by.references.begin (); r!=group_by.references.end ();)
    {
      os << *r;
      ++r;
      if (r!=group_by.references.end ())
        {
          os << ",";
        }
    }
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Group_By,
                           (std::vector<ADQL::Column_Reference>, references))
