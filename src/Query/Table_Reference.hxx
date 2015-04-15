#pragma once

#include <iostream>
#include <string>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "Table_Reference/Correlation_Join.hxx"
#include "Joined_Table_Wrap.hxx"

namespace ADQL
{
class Table_Reference
{
public:
  typedef boost::variant<Table_Correlation, Correlation_Join,
                         Joined_Table_Wrap> Variant;
  Variant variant;
  bool empty () const;
};
}

namespace
{
class Table_Reference_Variant_Visitor
    : public boost::static_visitor<bool>
{
public:
  bool operator()(const ADQL::Table_Correlation &s) const
  {
    return s.empty();
  }
  bool operator()(const ADQL::Correlation_Join &s) const
  {
    return s.empty();
  }
  bool operator()(const ADQL::Joined_Table_Wrap &s) const
  {
    return ADQL::empty (s);
  }
};
}

inline bool ADQL::Table_Reference::empty () const
{
  Table_Reference_Variant_Visitor visitor;
  return boost::apply_visitor (visitor, variant);
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
