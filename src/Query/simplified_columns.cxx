#include "../Query.hxx"

namespace {
class Column_Visitor
        : public boost::static_visitor<std::pair<std::string, std::string> > {
public:
    std::pair<std::string, std::string> operator()(const ADQL::Non_As &non_as) {
        std::string s(ADQL::to_string(non_as));
        return std::make_pair(s, s);
    }

    std::pair<std::string, std::string> operator()(const ADQL::As &as) {
        return std::make_pair(to_string(as.expression), as.as);
    }
};

class Columns_Visitor : public boost::static_visitor<> {
public:
    std::vector<std::pair<std::string, std::string> > &v;
    Columns_Visitor(std::vector<std::pair<std::string, std::string> > &V) : v(V) {}
    Columns_Visitor() = delete;

    void operator()(const std::string &s) { v.emplace_back(s, ""); }

    void operator()(const std::vector<ADQL::Select::Column_Variant> &columns) {
        Column_Visitor visitor;
        for (auto &c : columns) v.push_back(boost::apply_visitor(visitor, c));
    }
};
}  // namespace

std::vector<std::pair<std::string, std::string> > ADQL::Query::simplified_columns(
        uint idx) const {
    std::vector<std::pair<std::string, std::string> > result;
    Columns_Visitor visitor(result);
    boost::apply_visitor(visitor, query_specification.get_sfw(idx).select.columns);
    return result;
}
