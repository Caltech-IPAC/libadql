#include "../Joined_Table.hxx"
#include "../Joined_Table_Wrap.hxx"

namespace ADQL {
bool empty(const Joined_Table_Wrap &j) { return j.get().empty(); }
}  // namespace ADQL
