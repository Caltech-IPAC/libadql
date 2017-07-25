#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Coalesce
{
public:
  std::string coalesce;
  bool empty () const { return coalesce.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Coalesce &coalesce)
{
  return os << coalesce.coalesce;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Coalesce, (std::string, coalesce))
