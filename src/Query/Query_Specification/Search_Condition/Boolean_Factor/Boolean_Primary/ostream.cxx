#include "../../../../Query_Specification.hxx"
#include "../Boolean_Primary.hxx"
#include "../../../Search_Condition.hxx"
#include "../../Joined_Table.hxx"

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

  std::ostream &operator()(const std::string &s) const { return os << s; }
};
}

namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                                const ADQL::Boolean_Primary &b)
{
  Boolean_Primary_Variant_Visitor visitor (os);
  return boost::apply_visitor (visitor, b.variant);
}
}
