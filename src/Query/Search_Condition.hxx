#pragma once

#include "Search_Condition/Boolean_Factor.hxx"

namespace ADQL
{
class Search_Condition
{
public:
  Boolean_Factor boolean_factor;
};
}

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Search_Condition &s)
{
  return os << s.boolean_factor;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Search_Condition,
                           (ADQL::Boolean_Factor, boolean_factor))

