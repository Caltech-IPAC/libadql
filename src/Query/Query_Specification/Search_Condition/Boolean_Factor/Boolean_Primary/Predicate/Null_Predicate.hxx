#pragma once

#include "../../../../Value_Expression_Non_Bool_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Null_Predicate
{
public:
  Value_Expression_Non_Bool_Wrap column;
  std::string Not;
  bool empty () const { return ADQL::empty (column); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Null_Predicate &c)
{
  return os << c.column << " IS " << (c.Not.empty () ? "" : "NOT ") << "NULL";
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Null_Predicate,
                           (ADQL::Value_Expression_Non_Bool_Wrap,
                            column)(std::string, Not))
