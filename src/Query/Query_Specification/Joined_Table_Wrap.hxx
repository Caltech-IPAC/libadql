#pragma once

namespace ADQL
{
class Joined_Table;
typedef boost::recursive_wrapper<Joined_Table> Joined_Table_Wrap;
bool empty (const Joined_Table_Wrap &);
}
