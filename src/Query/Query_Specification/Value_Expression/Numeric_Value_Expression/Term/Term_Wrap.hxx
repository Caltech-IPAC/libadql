#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL
{
class Term;
typedef boost::recursive_wrapper<Term> Term_Wrap;
std::ostream &operator<<(std::ostream &os, const Term_Wrap &s);
}
