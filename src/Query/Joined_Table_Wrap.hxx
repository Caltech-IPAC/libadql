#pragma once

namespace ADQL
{
class Joined_Table;
typedef boost::recursive_wrapper<Joined_Table> Joined_Table_Wrap;
std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table_Wrap &j);
bool empty (const Joined_Table_Wrap &);
}
