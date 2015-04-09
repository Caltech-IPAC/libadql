#pragma once

#include <boost/algorithm/string.hpp>
#include "Search_Condition/Boolean_Term.hxx"


namespace ADQL
{
class Search_Condition
{
public:
  /// There is only going to be zero or one Search_Condition::Variant,
  /// but we need to put it into a structure that does not create a
  /// Search_Condition::Variant by default.  Otherwise,
  /// Search_Condition::Variant creates a Search_Condition, which
  /// creates a Search_Condition::Variant, and so on until we run out
  /// of stack space :(
  typedef boost::variant<Boolean_Factor, Boolean_Term> Variant;

  std::vector<Variant> variant;

  bool empty () const { return variant.empty (); }
  std::string string() const;
};
}

namespace
{
class Search_Condition_Variant_Visitor
    : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Search_Condition_Variant_Visitor (std::ostream &OS) : os (OS) {}
  Search_Condition_Variant_Visitor () = delete;

  std::ostream &operator()(const ADQL::Boolean_Term &s) const
  {
    return os << s;
  }

  std::ostream &operator()(const ADQL::Boolean_Factor &s) const
  {
    return os << s;
  }
};
}

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Search_Condition &s)
{
  if (!s.empty ())
    {
      Search_Condition_Variant_Visitor visitor (os);
      return boost::apply_visitor (visitor, s.variant[0]);
    }
  return os;
}

inline std::ostream &operator<<(std::ostream &os, const Search_Condition_Wrap &s)
{
  return os << s.get ();
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Search_Condition,
                           (std::vector<ADQL::Search_Condition::Variant>,
                            variant))
