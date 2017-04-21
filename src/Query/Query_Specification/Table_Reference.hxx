#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Table_Reference/Correlation_Join.hxx"
#include "Joined_Table_Wrap.hxx"
#include "Derived_Correlation.hxx"
#include "../empty_variant.hxx"

namespace ADQL
{
class Table_Reference
{
public:
  typedef boost::variant<Table_Correlation, Joined_Table_Wrap,
                         Derived_Correlation> Variant;
  Variant variant;
  bool empty () const
  {
    return empty_variant (variant);
  }
};
}

inline bool ADQL::empty (const Table_Reference_Wrap &t)
{
  return t.get ().empty ();
}

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os, const ADQL::Table_Reference &table)
{
  return os << table.variant;
}

inline std::ostream &operator<<(std::ostream &os, const ADQL::Table_Reference_Wrap &j)
{
  return os << j.get ();
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Table_Reference,
                           (ADQL::Table_Reference::Variant, variant))
