#pragma once

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"
#include "Query/As.hxx"
#include "Query/Where.hxx"
#include "Query/Having.hxx"

namespace ADQL
{
class Query
{
public:
  typedef boost::variant<As, std::string> Column_Variant;
  typedef boost::variant<std::string, std::vector<Column_Variant> > Columns;

  Columns columns;
  std::string all_or_distinct;
  size_t top;
  std::vector<std::string> tables;
  Where where;
  std::string group_by, order_by;
  Having having;
  Query (const std::string &input, const std::map<std::string,std::string> &table_mapping);
  Query (const std::string &input): Query(input,{{}}) {}

  std::vector<std::pair<std::string,std::string> > simplified_columns() const;

  bool simple_query() const
  {
    return (all_or_distinct.empty() || all_or_distinct=="ALL")
      && where.search_condition.empty()
      && group_by.empty() && order_by.empty()
      && having.empty();
  }

  std::string string() const;
};
}

namespace
{
class Query_Columns_Visitor : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Query_Columns_Visitor (std::ostream &OS) : os (OS) {}
  Query_Columns_Visitor () = delete;

  std::ostream &operator()(const std::string &s) const { return os << s; }

  std::ostream &operator()(const std::vector<ADQL::Query::Column_Variant> &s)
      const
  {
    std::stringstream ss;
    for (auto &o : s)
      {
        ss << o << ", ";
      }
    std::string temp = ss.str ();
    /// Trim off the trailing comma
    temp = temp.substr (0, temp.size () - 2);
    return os << temp;
  }
};
}


namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Query::Columns &columns)
{
  Query_Columns_Visitor visitor (os);
  return boost::apply_visitor (visitor, columns);
}

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Query &query)
{
  os << "SELECT "
     << query.all_or_distinct
     << (query.all_or_distinct.empty() ? "" : " ")
     << (query.top!=std::numeric_limits<unsigned long long>::max()
         ? "TOP " + std::to_string(query.top) + " " : "")
     << query.columns
     << " FROM " << query.tables.at(0);
  for(size_t i=1; i<query.tables.size(); ++i)
    os << ", " << query.tables.at(i);
  if(!query.where.empty())
    os << " WHERE " << query.where;
  if(!query.group_by.empty())
    os << " GROUP BY " << query.group_by;
  if(!query.having.empty())
    os << " HAVING " << query.having;
  if(!query.order_by.empty())
    os << " ORDER BY " << query.order_by;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (
    ADQL::Query,
    (std::string, all_or_distinct)(size_t, top)(ADQL::Query::Columns,
                                                columns)
    (std::vector<std::string>, tables)(
        ADQL::Where, where)(std::string, group_by)(ADQL::Having,
                                                   having)(std::string,
                                                           order_by))
