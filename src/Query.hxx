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
#include "Query/Table_Reference.hxx"
#include "Query/Search_Condition/Joined_Table.hxx"

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
  std::vector<Table_Reference> tables;
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
    auto o=s.begin ();
    if (o!=s.end ())
      {
        os << *o;
        ++o;
      }
    for (; o!=s.end (); ++o)
      os << ", " << *o;
    return os;
  }
};
}


namespace ADQL
{
inline std::ostream &operator<<(std::ostream &os,
                                const std::vector<Table_Reference> &tables)
{
  auto table=tables.begin ();
  if (table!=tables.end ())
    {
      os << *table;
      // os << table->name;
      ++table;
    }
  for (; table!=tables.end (); ++table)
    os << ", " << *table;
    // os << ", " << table->name;
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Query::Columns &columns)
{
  return boost::apply_visitor (Query_Columns_Visitor (os), columns);
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
     << " FROM " << query.tables;
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
    (std::vector<ADQL::Table_Reference>, tables)(
        ADQL::Where, where)(std::string, group_by)(ADQL::Having,
                                                   having)(std::string,
                                                           order_by))
