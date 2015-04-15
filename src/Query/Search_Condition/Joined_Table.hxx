#pragma once

#include "Joined_Table/Qualified_Join.hxx"
#include "../Joined_Table_Wrap.hxx"

namespace ADQL
{
class Joined_Table
{
public:
  typedef boost::variant<Qualified_Join, Joined_Table_Wrap> Variant;
  Variant variant;
  Join_Suffix join_suffix;
  bool empty () const;
};
  std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table_Wrap &j);
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
    return os << "(" << s << ")";
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

inline std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table_Wrap &j)
{
  return os << j.get ();
}
}


namespace
{
class Joined_Table_empty_Visitor
    : public boost::static_visitor<bool>
{
public:
  bool operator()(const ADQL::Qualified_Join &s) const
  {
    return s.empty ();
  }

  bool operator()(const ADQL::Joined_Table_Wrap &s) const
  {
    return ADQL::empty (s);
  }
};
}

inline bool ADQL::Joined_Table::empty() const
{
  Joined_Table_empty_Visitor visitor;
  return boost::apply_visitor (visitor, variant);
}

inline bool ADQL::empty(const ADQL::Joined_Table_Wrap &j)
{
  return j.get ().empty ();
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Joined_Table,
                           (ADQL::Joined_Table::Variant, variant)
                           (ADQL::Join_Suffix, join_suffix))
