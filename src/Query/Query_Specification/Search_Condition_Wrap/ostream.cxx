#include "../Search_Condition.hxx"
#include "../Search_Condition_Wrap.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const Search_Condition_Wrap &s) {
    return os << s.get();
}
}  // namespace ADQL
