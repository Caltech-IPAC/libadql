#pragma once

#include "../../Search_Condition_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>

namespace ADQL
{
class Join_Condition
{
public:
  Search_Condition_Wrap search_condition_wrap;
  bool empty () const { return ADQL::empty (search_condition_wrap); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Join_Condition &j)
{
  return os << "ON " << j.search_condition_wrap;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Join_Condition, (ADQL::Search_Condition_Wrap,
                                                  search_condition_wrap))
