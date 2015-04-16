#pragma once

#include "Join_Specification/Join_Condition.hxx"
#include "Join_Specification/Named_Columns_Join.hxx"

namespace
{
class Join_Specification_empty_Visitor
    : public boost::static_visitor<bool>
{
public:
  bool operator()(const ADQL::Join_Condition &s) const
  {
    return s.empty ();
  }

  bool operator()(const ADQL::Named_Columns_Join &s) const
  {
    return s.empty ();
  }
};
}

namespace ADQL
{
class Join_Specification
{
public:
  typedef boost::variant<Named_Columns_Join, Join_Condition> Variant;
  Variant variant;
  bool empty() const
  {
    Join_Specification_empty_Visitor visitor;
    return boost::apply_visitor (visitor, variant);
  }
};
}

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Join_Specification &j)
{
  return os << j.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Join_Specification,
                           (ADQL::Join_Specification::Variant, variant))
