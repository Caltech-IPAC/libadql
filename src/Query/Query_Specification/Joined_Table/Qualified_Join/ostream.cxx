#include "../../../Query_Specification.hxx"
#include "../../Joined_Table.hxx"
#include "../../Search_Condition.hxx"
#include "../Qualified_Join.hxx"

namespace {
class Qualified_Join_ostream_Visitor : public boost::static_visitor<std::ostream &> {
public:
    std::ostream &os;
    Qualified_Join_ostream_Visitor(std::ostream &OS) : os(OS) {}
    Qualified_Join_ostream_Visitor() = delete;

    std::ostream &operator()(const ADQL::Table_Correlation &s) const { return os << s; }

    std::ostream &operator()(const ADQL::Joined_Table_Wrap &s) const {
        return os << s.get();
    }
};
}  // namespace

namespace ADQL {
std::ostream &operator<<(std::ostream &os, const Qualified_Join &j) {
    Qualified_Join_ostream_Visitor visitor(os);
    boost::apply_visitor(visitor, j.variant);
    os << " ";
    for (auto &suffix : j.join_suffixes) {
        os << suffix << " ";
    }
    return os;
}
}  // namespace ADQL
