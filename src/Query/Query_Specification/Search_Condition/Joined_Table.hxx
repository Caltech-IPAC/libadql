#pragma once

#include "Joined_Table/Qualified_Join.hxx"
#include "../Joined_Table_Wrap.hxx"
#include "../../empty_variant.hxx"

namespace ADQL
{
class Joined_Table
{
public:
  typedef boost::variant<Qualified_Join, Joined_Table_Wrap> Variant;
  Variant variant;
  Join_Suffix join_suffix;
  bool empty () const
  {
    return empty_variant (variant);
  }
};
  std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table &j);
}


namespace
{
class Joined_Table_ostream_Visitor
    : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Joined_Table_ostream_Visitor (std::ostream &OS) : os (OS) {}
  Joined_Table_ostream_Visitor () = delete;

  std::ostream &operator()(const ADQL::Qualified_Join &s) const
  {
    return os << s;
  }

  std::ostream &operator()(const ADQL::Joined_Table_Wrap &s) const
  {
    return os << "(" << s.get () << ")";
  }
};
}

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Joined_Table &j)
{
  Joined_Table_ostream_Visitor visitor(os);
  boost::apply_visitor (visitor, j.variant);
  if (!j.join_suffix.empty ())
    os << j.join_suffix;
  return os;
}
}

inline bool ADQL::empty(const ADQL::Joined_Table_Wrap &j)
{
  return j.get ().empty ();
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Joined_Table,
                           (ADQL::Joined_Table::Variant, variant)
                           (ADQL::Join_Suffix, join_suffix))
