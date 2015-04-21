#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Correlation_Join/Table_Correlation.hxx"
#include "../Join_Suffix.hxx"

namespace ADQL
{
class Correlation_Join
{
public:
  Table_Correlation table_correlation;
  Join_Suffix join_suffix;

  bool empty () const
  {
    return table_correlation.empty ();
  }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Correlation_Join &t)
{
  os << t.table_correlation << " ";
  if (!t.join_suffix.empty ())
    os << t.join_suffix;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Correlation_Join,
                           (ADQL::Table_Correlation, table_correlation)
                           (ADQL::Join_Suffix, join_suffix))
