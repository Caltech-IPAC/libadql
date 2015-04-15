#pragma once

namespace ADQL
{
class Table_Reference;
typedef boost::recursive_wrapper<Table_Reference> Table_Reference_Wrap;
std::ostream &operator<<(std::ostream &os, const ADQL::Table_Reference_Wrap &j);
bool empty (const Table_Reference_Wrap &t);
}
