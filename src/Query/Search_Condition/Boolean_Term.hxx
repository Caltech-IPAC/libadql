#pragma once

#include <boost/variant/recursive_wrapper.hpp>
#include "Boolean_Factor.hxx"

namespace ADQL
{
class Search_Condition;
typedef boost::recursive_wrapper<Search_Condition> Search_Condition_Wrap;

class Boolean_Term
{
public:
  Search_Condition_Wrap search_condition_wrap;
  std::string logical_op;
  Boolean_Factor boolean_factor;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Boolean_Term,
                           (ADQL::Boolean_Factor, boolean_factor)
                           (std::string, logical_op)
                           (ADQL::Search_Condition_Wrap, search_condition_wrap))
