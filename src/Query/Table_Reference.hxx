#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Table_Reference/Table_Correlation.hxx"

namespace ADQL
{
class Table_Reference
{
public:
  Table_Correlation table_correlation;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Table_Reference &table)
{
  return os << table.table_correlation;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Table_Reference,
                           (ADQL::Table_Correlation, table_correlation))
