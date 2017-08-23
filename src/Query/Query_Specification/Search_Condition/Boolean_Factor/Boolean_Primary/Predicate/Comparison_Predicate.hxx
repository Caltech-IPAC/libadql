#pragma once

#include "../../../../Value_Expression_Non_Bool_Wrap.hxx"
#include "../../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Comparison_Predicate
{
public:
  // std::string left;
  Value_Expression_Non_Bool_Wrap left;
  // std::string right;
  Value_Expression_Wrap right;
  std::string op;
  bool empty () const { return op.empty (); }
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Comparison_Predicate &c);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Comparison_Predicate,
                           // (std::string,
                           (ADQL::Value_Expression_Non_Bool_Wrap,
                            // left)(std::string, op)(std::string,
                            left)(std::string, op)(ADQL::Value_Expression_Wrap,
                                                   right))
