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
  std::vector<std::string> coalesce;
  bool empty () const { return coalesce.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Coalesce &coalesce)
{
  os << "COALESCE(";
  for (auto c=coalesce.coalesce.begin (); c!=coalesce.coalesce.end (); )
    {
      os << *c;
      ++c;
      if (c!=coalesce.coalesce.end ())
        {
          os << ',';
        }
    }
  os << ')';
  return os;
}
}

  BOOST_FUSION_ADAPT_STRUCT (ADQL::Coalesce, (std::vector<std::string>, coalesce))
