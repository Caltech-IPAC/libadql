#pragma once

#include <boost/variant/recursive_wrapper.hpp>

#include <iostream>

namespace ADQL
{
class Subquery;
typedef boost::recursive_wrapper<Subquery> Subquery_Wrap;
std::ostream &operator<<(std::ostream &os, const Subquery_Wrap &s);
bool empty (const Subquery_Wrap &);
}
