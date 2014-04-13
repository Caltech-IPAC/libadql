#pragma once

#include "Geometry.hxx"
#include "Search_Condition.hxx"

namespace ADQL
{
class Where
{
public:
  Search_Condition search_condition;
  Geometry geometry;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Where,
                           (ADQL::Geometry, geometry)
                           (ADQL::Search_Condition, search_condition))
