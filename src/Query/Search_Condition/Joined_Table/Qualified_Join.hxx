#pragma once

#include "Qualified_Join/Join_Specification.hxx"
#include "Qualified_Join/Outer_Join.hxx"

namespace ADQL
{
class Qualified_Join
{
public:
  Table_Correlation table_correlation;
  Table_Reference table_reference;
  typedef boost::variant<std::string, Outer_Join> Join_Type;
  Join_Type join_type;
  bool natural=false;
  Join_Specification join_specification;
};

inline std::ostream &operator<<(std::ostream &os, const Qualified_Join &j)
{
  os << j.table_correlation << " ";
  if (j.natural)
    os << "NATURAL ";
  if (!j.join_type.empty ())
    os << j.join_type << " ";
  os << "JOIN "
     << j.table_reference;
  if (!j.join_specification.empty ())
    os << " " << j.join_specification;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Qualified_Join,
                           (ADQL::Table_Correlation, table_correlation)
                           (bool, natural)
                           (ADQL::Qualified_Join::Join_Type, join_type)
                           (ADQL::Table_Reference, table_reference)
                           (ADQL::Join_Specification, join_specification))
