#include "../../../../../../Value_Expression.hxx"
#include "../Simple_When.hxx"

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const ADQL::Simple_When &simple_when) {
    return os << "WHEN " << simple_when.wrap << " "
              << "THEN " << simple_when.result;
}
}  // namespace ADQL
