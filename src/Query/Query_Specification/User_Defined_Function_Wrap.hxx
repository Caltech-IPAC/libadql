#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL
{
class User_Defined_Function;
typedef boost::recursive_wrapper<User_Defined_Function>
    User_Defined_Function_Wrap;
// std::ostream &operator<<(std::ostream &os,
//                          const User_Defined_Function_Wrap &s);
}
