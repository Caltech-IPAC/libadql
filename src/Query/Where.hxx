#pragma once

#include "Search_Condition.hxx"

namespace ADQL
{
class Where
{
public:
  Search_Condition search_condition;
};
}

inline std::ostream & operator<<(std::ostream &os, const Where &w)
{
  return os << "WHERE " << w.search_condition;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Where,
                           (ADQL::Search_Condition, search_condition))

