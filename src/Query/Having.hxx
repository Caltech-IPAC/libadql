#pragma once

#include "Search_Condition.hxx"

namespace ADQL
{
class Having
{
public:
  Search_Condition search_condition;
};
}
inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Having &having)
{
  return os << "HAVING " << having.search_condition;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Having,
                           (ADQL::Search_Condition, search_condition)
                           )
