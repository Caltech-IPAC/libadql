#include "../Joined_Table.hxx"
#include "../Search_Condition.hxx"
#include "../../Query_Specification.hxx"

namespace
{
class Joined_Table_ostream_Visitor
    : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Joined_Table_ostream_Visitor (std::ostream &OS) : os (OS) {}
  Joined_Table_ostream_Visitor () = delete;

  std::ostream &operator()(const ADQL::Qualified_Join &s) const
  {
    return os << s;
  }

  std::ostream &operator()(const ADQL::Joined_Table_Wrap &s) const
  {
    return os << "(" << s.get () << ")";
  }
};
}

namespace ADQL
{
std::ostream &operator<<(std::ostream &os, const ADQL::Joined_Table &j)
{
  Joined_Table_ostream_Visitor visitor (os);
  boost::apply_visitor (visitor, j.variant);
  return os;
}
}
