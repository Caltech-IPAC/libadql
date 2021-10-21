#pragma once

#include <boost/variant/recursive_wrapper.hpp>

namespace ADQL {
class Query_Specification;
typedef boost::recursive_wrapper<Query_Specification> Query_Specification_Wrap;
}  // namespace ADQL
