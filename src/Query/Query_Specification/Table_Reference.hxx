#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Table_Reference/Correlation_Join.hxx"
#include "Joined_Table_Wrap.hxx"
#include "Derived_Correlation.hxx"

namespace ADQL
{
class Table_Reference
{
public:
  typedef boost::variant<Table_Correlation, Joined_Table_Wrap,
                         Derived_Correlation> Variant;
  Variant variant;
  bool empty () const;
};

std::ostream &operator<<(std::ostream &os, const ADQL::Table_Reference &table);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Table_Reference,
                           (ADQL::Table_Reference::Variant, variant))
