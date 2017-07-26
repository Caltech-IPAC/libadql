#pragma once

#include "../Value_Expression_Primary_Wrap.hxx"
#include "../../User_Defined_Function_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include <iostream>

namespace ADQL
{
class Character_Factor
{
public:
  typedef boost::variant<User_Defined_Function_Wrap,
                         Value_Expression_Primary_Wrap> Variant;
  Variant variant;
  bool empty () const;
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Character_Factor &character_factor);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Character_Factor,
                           (ADQL::Character_Factor::Variant, variant))
