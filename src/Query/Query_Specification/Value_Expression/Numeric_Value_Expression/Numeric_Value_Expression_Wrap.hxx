#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL
{
class Numeric_Value_Expression;
typedef boost::recursive_wrapper<Numeric_Value_Expression>
    Numeric_Value_Expression_Wrap;
std::ostream &operator<<(std::ostream &os,
                         const Numeric_Value_Expression_Wrap &s);
}
