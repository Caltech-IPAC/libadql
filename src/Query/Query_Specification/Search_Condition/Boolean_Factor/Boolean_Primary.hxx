#pragma once

#include "Boolean_Primary/Predicate.hxx"

namespace ADQL
{
typedef boost::variant<Predicate, Search_Condition_Wrap>
Boolean_Primary_Variant;

class Boolean_Primary
{
public:
  Boolean_Primary_Variant variant;
};
}

namespace
{
class Boolean_Primary_Variant_Visitor
    : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Boolean_Primary_Variant_Visitor (std::ostream &OS) : os (OS) {}
  Boolean_Primary_Variant_Visitor () = delete;

  std::ostream &operator()(const ADQL::Predicate &s) const { return os << s; }

  std::ostream &operator()(const ADQL::Search_Condition_Wrap &s) const
  {
    return os << "(" << s << ")";
  }
};
}

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Boolean_Primary &b)
{
  Boolean_Primary_Variant_Visitor visitor (os);
  return boost::apply_visitor (visitor, b.variant);
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Boolean_Primary,
                           (ADQL::Boolean_Primary_Variant, variant))
