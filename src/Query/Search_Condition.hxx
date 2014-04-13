#pragma once

#include <boost/algorithm/string.hpp>
#include "Search_Condition/Boolean_Term.hxx"

namespace ADQL
{
typedef boost::variant<Boolean_Factor,Boolean_Term> Search_Condition_Variant;

class Search_Condition
{
public:
  /// There is only going to be zero or one Search_Condition_Variant,
  /// but we need to put it into a structure that does not create a
  /// Search_Condition_Variant by default.  Otherwise,
  /// Search_Condition_Variant creates a Search_Condition, which
  /// creates a Search_Condition_Variant, and so on until we run out
  /// of stack space :(
  std::vector<Search_Condition_Variant> search_condition_variant;
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



class my_visitor : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  my_visitor(std::ostream &OS): os(OS) {}
  my_visitor()=delete;

  std::ostream & operator()(const ADQL::Boolean_Term &s) const
  {
    return os << s;
  }
    
  std::ostream & operator()(const ADQL::Boolean_Factor &s) const
  {
    return os << s;
  }
};


inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Search_Condition &s)
{
  if(!s.search_condition_variant.empty())
    {
      my_visitor visitor(os);
      return boost::apply_visitor(visitor,s.search_condition_variant[0]);
    }
  return os;
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Search_Condition,
                           (std::vector<ADQL::Search_Condition_Variant>,
                            search_condition_variant))

