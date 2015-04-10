#pragma once

#include "../../../Search_Condition_Wrap.hxx"

namespace ADQL
{
class Join_Condition
{
public:
  Search_Condition_Wrap search_condition_wrap;
  bool empty () const { return ADQL::empty (search_condition_wrap); }
  std::string string() const;
};

std::ostream &operator<<(std::ostream &os, const ADQL::Join_Condition &j);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Join_Condition,
                           (ADQL::Search_Condition_Wrap, search_condition_wrap))
