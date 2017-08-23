#pragma once

#include "../../../../Value_Expression_Wrap.hxx"
#include "../../../../Value_Expression_Non_Bool_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Like_Predicate
{
public:
  Value_Expression_Non_Bool_Wrap match;
  Value_Expression_Wrap pattern;
  std::string Not;
  bool empty () const { return ADQL::empty (match); }
};

std::ostream &operator<<(std::ostream &os, const ADQL::Like_Predicate &c);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Like_Predicate,
                           (ADQL::Value_Expression_Non_Bool_Wrap,
                            match)(std::string,
                                   Not)(ADQL::Value_Expression_Wrap, pattern))
