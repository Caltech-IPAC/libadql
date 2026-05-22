#include "../Whitelisted_Function.hxx"
#include "../Whitelisted_Function_Wrap.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Whitelisted_Function_Wrap &wrap) {
    return os << wrap.get();
}
}  // namespace ADQL
