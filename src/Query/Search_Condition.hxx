#pragma once

#include <boost/algorithm/string.hpp>
#include "Search_Condition/Boolean_Term.hxx"

namespace ADQL
{
class Search_Condition
{
public:
  /// There is only going to be zero or one Search_Condition_Variant,
  /// but we need to put it into a structure that does not create a
  /// Search_Condition_Variant by default.  Otherwise,
  /// Search_Condition_Variant creates a Search_Condition, which
  /// creates a Search_Condition_Variant, and so on until we run out
  /// of stack space :(
  typedef boost::variant<Boolean_Factor,Boolean_Term> Variant;

  std::vector<Variant> variant;

  bool good() const
  {
    return !variant.empty();
  }
};
}

std::ostream & operator<<(std::ostream &os,
                          const ADQL::Search_Condition &s);

/// We have to define this operator here, because Search_Condition is
/// not defined in Boolean_Term.

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Boolean_Term &s)
{
  return os << s.boolean_factor << " " << boost::to_upper_copy(s.logical_op)
            << " " << s.search_condition_wrap.get();
}


namespace {
class Search_Condition_Variant_Visitor
  : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Search_Condition_Variant_Visitor(std::ostream &OS): os(OS) {}
  Search_Condition_Variant_Visitor()=delete;

  std::ostream & operator()(const ADQL::Boolean_Term &s) const
  {
    return os << s;
  }
    
  std::ostream & operator()(const ADQL::Boolean_Factor &s) const
  {
    return os << s;
  }
};
}

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Search_Condition &s)
{
  if(s.good())
    {
      Search_Condition_Variant_Visitor visitor(os);
      return boost::apply_visitor(visitor,s.variant[0]);
    }
  return os;
}

namespace {
class Boolean_Primary_Variant_Visitor
  : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Boolean_Primary_Variant_Visitor(std::ostream &OS): os(OS) {}
  Boolean_Primary_Variant_Visitor()=delete;

  std::ostream & operator()(const ADQL::Predicate &s) const
  {
    return os << s;
  }
    
  std::ostream & operator()(const ADQL::Search_Condition_Wrap &s) const
  {
    return os << "(" << s.get() << ")";
  }
};
}

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Boolean_Primary &b)
{
  Boolean_Primary_Variant_Visitor visitor(os);
  return boost::apply_visitor(visitor,b.variant);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Search_Condition,
                           (std::vector<ADQL::Search_Condition::Variant>,
                            variant))

