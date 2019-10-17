#pragma once

#include "Group_By_Term.hxx"

#include <vector>

namespace ADQL
{
class Group_By
{
public:
  std::vector<Group_By_Term> terms;
  bool empty () const { return terms.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Group_By &group_by)
{
  for (auto r=group_by.terms.begin (); r!=group_by.terms.end ();)
    {
      os << *r;
      ++r;
      if (r!=group_by.terms.end ())
        {
          os << ",";
        }
    }
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Group_By,
                           (std::vector<ADQL::Group_By_Term>, terms))
