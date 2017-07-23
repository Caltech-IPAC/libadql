#pragma once

#include "../../ostream_vector.hxx"
namespace ADQL
{
class Named_Columns_Join
{
public:
  std::vector<std::string> column_list;
  bool empty () const { return column_list.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Named_Columns_Join &j)
{
  return os << "USING " << j.column_list;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Named_Columns_Join,
                           (std::vector<std::string>, column_list))
