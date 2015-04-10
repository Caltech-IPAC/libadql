#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Table_Reference/Table_Correlation.hxx"
#include "Joined_Table_Wrap.hxx"

namespace ADQL
{
class Table_Reference
{
public:
  typedef boost::variant<Table_Correlation, Joined_Table_Wrap> Variant;

  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Table_Reference &table)
{
  return os << table.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Table_Reference,
                           (ADQL::Table_Reference::Variant, variant))
