#pragma once

#include "../../../../Number_Variant.hxx"
namespace ADQL
{
class In_Predicate
{
public:
  Number_Variant value;
  std::string Not;

  typedef boost::variant<std::vector<Number_Variant>,Number_Variant> Variant;
  Variant variant;
};
}

class In_Predicate_Visitor
  : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  In_Predicate_Visitor(std::ostream &OS): os(OS) {}
  In_Predicate_Visitor()=delete;

  std::ostream & operator()(const std::vector<ADQL::Number_Variant> &v) const
  {
    os << "(";
    for(auto n=v.begin(); n!=v.end();)
      {
        os << *n;
        ++n;
        if(n!=v.end())
          os << ", ";
      }
    os << ")";
    return os;
  }
    
  std::ostream & operator()(const ADQL::Number_Variant &v) const
  {
    return os << v;
  }
};


inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::In_Predicate &p)
{
  return os << p.value << " " << p.Not << (p.Not.empty() ? "" : " ")
            << "IN ";
  In_Predicate_Visitor visitor(os);
  return boost::apply_visitor(visitor,p.variant);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::In_Predicate,
                           (ADQL::Number_Variant, value)
                           (std::string, Not)
                           (ADQL::In_Predicate::Variant, variant))

