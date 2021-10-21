#include "../Subquery.hxx"
#include "../Subquery_Wrap.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Subquery_Wrap &wrap) {
    return os << wrap.get();
}
}  // namespace ADQL
