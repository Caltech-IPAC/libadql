#pragma once

#include "Join_Specification/Join_Condition.hxx"

namespace
{
class Join_Specification_Variant_Visitor
    : public boost::static_visitor<bool>
{
public:
  bool operator()(const ADQL::Join_Condition &s) const
  {
    return s.empty();
  }

  bool operator()(const std::string &s) const
  {
    return s.empty();
  }
};
}

namespace ADQL
{
class Join_Specification
{
public:
  typedef boost::variant<std::string, Join_Condition> Variant;
  Variant variant;
  bool empty() const
  {
    Join_Specification_Variant_Visitor visitor;
    return boost::apply_visitor (visitor, variant);
  }
};

inline std::ostream &operator<<(std::ostream &os, const Join_Specification &j)
{
  return os << j.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Join_Specification,
                           (ADQL::Join_Specification::Variant, variant))
