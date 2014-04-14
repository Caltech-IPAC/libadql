#pragma once

#include "Predicate/Comparison_Predicate.hxx"
#include "Predicate/Between_Predicate.hxx"

namespace ADQL
{
typedef boost::variant<Comparison_Predicate,Between_Predicate> Predicate_Variant;

class Predicate
{
public:
  Predicate_Variant predicate_variant;
};
}

class Predicate_Variant_visitor
  : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Predicate_Variant_visitor(std::ostream &OS): os(OS) {}
  Predicate_Variant_visitor()=delete;

  std::ostream & operator()(const ADQL::Comparison_Predicate &s) const
  {
    return os << s;
  }
    
  std::ostream & operator()(const ADQL::Between_Predicate &s) const
  {
    return os << s;
  }
};


inline std::ostream & operator<<(std::ostream &os, const ADQL::Predicate &p)
{
  Predicate_Variant_visitor visitor(os);
  return boost::apply_visitor(visitor,p.predicate_variant);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Predicate,
                           (ADQL::Predicate_Variant, predicate_variant))

