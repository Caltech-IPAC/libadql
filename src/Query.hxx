#pragma once

#include <vector>
#include <string>
#include <boost/fusion/include/io.hpp>
#include "boost/variant.hpp"
#include "Query/As.hxx"
#include "Query/Where.hxx"

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
  std::string table;
  Where where;
  std::string group_by, order;
  Search_Condition having;
  Query (const std::string &input);
};
}

namespace {
class Query_Columns_Visitor
  : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Query_Columns_Visitor(std::ostream &OS): os(OS) {}
  Query_Columns_Visitor()=delete;

  std::ostream & operator()(const std::string &s) const
  {
    return os << s;
  }
    
  std::ostream & operator()(const std::vector<ADQL::Query::Column_Variant> &s)
    const
  {
    std::stringstream ss;
    for(auto &o: s)
      {
        ss << o << ", ";
      }        
    std::string temp=ss.str();
    /// Trim off the trailing comma
    temp=temp.substr(0,temp.size()-2);
    return os << temp;
  }
};
}

inline std::ostream & operator<<(std::ostream &os,
                                 const ADQL::Query::Columns &columns)
{
  Query_Columns_Visitor visitor(os);
  return boost::apply_visitor(visitor,columns);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Query,
                           (std::string, all_or_distinct)
                           (size_t, top)
                           (ADQL::Query::Columns, columns)
                           (std::string, table)
                           (ADQL::Where, where)
                           (std::string, group_by)
                           (ADQL::Search_Condition, having)
                           (std::string, order)
                           )

