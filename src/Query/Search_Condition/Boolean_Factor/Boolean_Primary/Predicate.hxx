#pragma once

#include "Predicate/Comparison_Predicate.hxx"
#include "Predicate/Between_Predicate.hxx"
#include "Predicate/In_Predicate.hxx"
#include "Predicate/Null_Predicate.hxx"

namespace ADQL
{
class Predicate
{
public:
  typedef boost::variant<Comparison_Predicate,Between_Predicate,
                         In_Predicate, Null_Predicate> Variant;
  Variant variant;
};
}

namespace {
class Predicate_Variant_Visitor
  : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Predicate_Variant_Visitor(std::ostream &OS): os(OS) {}
  Predicate_Variant_Visitor()=delete;

  std::ostream & operator()(const ADQL::Comparison_Predicate &s) const
  {
    return os << s;
  }
  std::ostream & operator()(const ADQL::Between_Predicate &s) const
  {
    return os << s;
  }
  std::ostream & operator()(const ADQL::In_Predicate &s) const
  {
    return os << s;
  }
  std::ostream & operator()(const ADQL::Null_Predicate &s) const
  {
    return os << s;
  }
};
}

inline std::ostream & operator<<(std::ostream &os, const ADQL::Predicate &p)
{
  Predicate_Variant_Visitor visitor(os);
  return boost::apply_visitor(visitor,p.variant);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Predicate,
                           (ADQL::Predicate::Variant, variant))

