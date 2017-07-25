#include "../Table_Reference.hxx"
#include "../Joined_Table.hxx"

#include <iostream>

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Table_Reference &table)
{
  return os << table.variant;
}
}
