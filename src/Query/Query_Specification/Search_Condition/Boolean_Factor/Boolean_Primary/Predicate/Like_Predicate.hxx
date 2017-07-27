#pragma once

#include "../../../../String_Value_Expression.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Like_Predicate
{
public:
  String_Value_Expression match, pattern;
  std::string Not;
};

std::ostream &operator<<(std::ostream &os, const ADQL::Like_Predicate &c);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Like_Predicate,
                           (ADQL::String_Value_Expression,
                            match)(std::string,
                                   Not)(ADQL::String_Value_Expression,
                                        pattern))
