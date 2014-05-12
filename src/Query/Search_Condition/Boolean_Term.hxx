#pragma once

#include "Search_Condition_Wrap.hxx"
#include "Boolean_Factor.hxx"

namespace ADQL
{
class Boolean_Term
{
public:
  Search_Condition_Wrap search_condition_wrap;
  std::string logical_op;
  Boolean_Factor boolean_factor;
};
}

BOOST_FUSION_ADAPT_STRUCT (
    ADQL::Boolean_Term,
    (ADQL::Boolean_Factor,
     boolean_factor)(std::string, logical_op)(ADQL::Search_Condition_Wrap,
                                              search_condition_wrap))
