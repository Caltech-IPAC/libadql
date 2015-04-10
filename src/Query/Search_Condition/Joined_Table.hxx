#pragma once

#include "Joined_Table/Qualified_Join.hxx"

namespace ADQL
{
class Joined_Table;
typedef boost::recursive_wrapper<Joined_Table> Joined_Table_Wrap;

class Joined_Table
{
public:
  typedef boost::variant<Qualified_Join, Joined_Table_Wrap> Variant;
  Variant variant;
};
  std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table_Wrap &j);
}


namespace
{
class Joined_Table_Variant_Visitor
    : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Joined_Table_Variant_Visitor (std::ostream &OS) : os (OS) {}
  Joined_Table_Variant_Visitor () = delete;

  std::ostream &operator()(const ADQL::Qualified_Join &s) const
  {
    return os << s;
  }

  std::ostream &operator()(const ADQL::Joined_Table_Wrap &s) const
  {
    return os << "(" << s << ")";
  }
};
}

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Joined_Table &j)
{
  Joined_Table_Variant_Visitor visitor(os);
  return boost::apply_visitor (visitor, j.variant);
}

inline std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table_Wrap &j)
{
  return os << j.get ();
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Joined_Table,
                           (ADQL::Joined_Table::Variant,
                            variant))
