#pragma once

#include "Value_Expression_Non_Bool.hxx"
#include "Search_Condition_Wrap.hxx"

namespace ADQL
{
class Value_Expression
{
public:
  typedef boost::variant<Value_Expression_Non_Bool, Search_Condition_Wrap>
      Variant;
  Variant variant;
  bool empty () const;
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Value_Expression &value_expression);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression,
                           (ADQL::Value_Expression::Variant, variant))
