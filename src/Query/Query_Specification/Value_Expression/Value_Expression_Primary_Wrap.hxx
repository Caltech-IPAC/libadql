#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL
{
class Value_Expression_Primary;
typedef boost::recursive_wrapper<Value_Expression_Primary> Value_Expression_Primary_Wrap;
std::ostream &operator<<(std::ostream &os, const Value_Expression_Primary_Wrap &s);
}
