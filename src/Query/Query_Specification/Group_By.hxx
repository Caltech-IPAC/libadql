#pragma once

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Group_By
{
public:
  std::string references;
  bool empty () const { return references.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Group_By &group_by)
{
  return os << group_by.references;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Group_By, (std::string, references))
