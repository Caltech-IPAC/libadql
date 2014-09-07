#pragma once

namespace ADQL
{
class In_Predicate
{
public:
  std::string value;
  std::string Not;

  typedef boost::variant<std::vector<std::string>, std::string> Variant;
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
    os << "(";
    for (auto n = v.begin (); n != v.end ();)
      {
        os << *n;
        ++n;
        if (n != v.end ())
          os << ", ";
      }
    os << ")";
    return os;
  }

  std::ostream &operator()(const std::string &v) const { return os << v; }
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
                           (std::string,
                            value)(std::string,
                                   Not)(ADQL::In_Predicate::Variant, variant))
