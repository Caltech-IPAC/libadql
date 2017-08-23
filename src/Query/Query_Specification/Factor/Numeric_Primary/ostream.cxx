#include "../Numeric_Primary.hxx"
#include "../../Value_Expression_Primary.hxx"

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Numeric_Primary &numeric_primary)
{
  return os << numeric_primary.variant;
}
}
