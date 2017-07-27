#pragma once

#include "../../../User_Defined_Function_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Boolean_Value_Expression
{
public:
  typedef boost::variant<std::string, User_Defined_Function_Wrap>
      Variant;
  Variant variant;
};
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Boolean_Value_Expression &b);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Boolean_Value_Expression,
                           (ADQL::Boolean_Value_Expression::Variant, variant))
