#include "../Value_Expression_Non_Bool.hxx"
#include "../Value_Expression_Non_Bool_Wrap.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Value_Expression_Non_Bool_Wrap &wrap) {
    return os << wrap.get();
}
}  // namespace ADQL
