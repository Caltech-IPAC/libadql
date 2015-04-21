#pragma once

namespace ADQL
{
class Query_Specification;
typedef boost::recursive_wrapper<Query_Specification> Query_Specification_Wrap;
std::ostream &operator<<(std::ostream &os, const ADQL::Query_Specification_Wrap &j);
}
