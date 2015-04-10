#pragma once

#include "Qualified_Join/Join_Specification.hxx"

namespace ADQL
{
class Qualified_Join
{
public:
  Table table_reference1, table_reference2;
  std::string join_type;
  bool natural=false;
  Join_Specification join_specification;
};

inline std::ostream &operator<<(std::ostream &os, const Qualified_Join &j)
{
  os << j.table_reference1 << " ";
  if (j.natural)
    os << "NATURAL ";
  if (!j.join_type.empty ())
    os << j.join_type << " ";
  os << " JOIN "
     << j.table_reference2;
  if (!j.join_specification.empty ())
    os << " " << j.join_specification;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Qualified_Join,
                           (ADQL::Table, table_reference1)
                           (bool, natural)
                           (std::string, join_type)
                           (ADQL::Table, table_reference2)
                           (ADQL::Join_Specification, join_specification))
