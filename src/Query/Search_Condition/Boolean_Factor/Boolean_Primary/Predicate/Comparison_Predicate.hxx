#pragma once

#include <string>
#include <sstream>
#include <boost/fusion/include/adapt_struct.hpp>

namespace ADQL
{
class Comparison_Predicate
{
public:
  std::string left, right;
  std::string op;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Comparison_Predicate &c)
{
  return os << c.left << " " << c.op << " " << c.right;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Comparison_Predicate,
                           (std::string, left)(std::string, op)(std::string,
                                                                right))
