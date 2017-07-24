#include "../Joined_Table_Wrap.hxx"
#include "../Joined_Table.hxx"

namespace ADQL
{
bool empty (const Joined_Table_Wrap &j) { return j.get ().empty (); }
}
