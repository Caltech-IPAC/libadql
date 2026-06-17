#include "../Window_Function.hxx"
#include "../Window_Function_Wrap.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Window_Function_Wrap &wrap) {
    return os << wrap.get();
}
}  // namespace ADQL
