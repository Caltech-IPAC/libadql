#pragma once

#include <string>
#include <sstream>
#include <boost/fusion/include/adapt_struct.hpp>
#include "boost/variant.hpp"
#include "../../../../ostream_vector_string.hxx"
#include "../../../../../Subquery.hxx"

namespace ADQL
{
class In_Predicate
{
public:
  Value_Expression value;
  std::string Not;

  typedef boost::variant<std::vector<std::string>, Subquery> Variant;
  Variant variant;
};
}

namespace
{
class In_Predicate_Visitor : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  In_Predicate_Visitor (std::ostream &OS) : os (OS) {}
  In_Predicate_Visitor () = delete;

  std::ostream &operator()(const std::vector<std::string> &v) const
  {
    using namespace ADQL;
    return os << v;
  }

  std::ostream &operator()(const ADQL::Subquery &subquery) const
  {
    return os << subquery;
  }
};
}

namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os, const ADQL::In_Predicate &p)
{
  os << p.value << " " << (p.Not.empty () ? "" : "NOT ") << "IN ";
  In_Predicate_Visitor visitor (os);
  return boost::apply_visitor (visitor, p.variant);
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::In_Predicate,
                           (ADQL::Value_Expression,
                            value)(std::string,
                                   Not)(ADQL::In_Predicate::Variant, variant))
