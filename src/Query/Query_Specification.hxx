#pragma once

#include "Query_Specification/As.hxx"
#include "Query_Specification/Non_As.hxx"
#include "Query_Specification/Where.hxx"
#include "Query_Specification/Group_By.hxx"
#include "Query_Specification/Order_By.hxx"
#include "Query_Specification/Having.hxx"
#include "Query_Specification/Table_Reference.hxx"
#include "Query_Specification/Joined_Table.hxx"
#include "Query_Specification/User_Defined_Function.hxx"

namespace ADQL
{
class Query_Specification
{
public:
  typedef boost::variant<As, Non_As> Column_Variant;
  typedef boost::variant<std::string, std::vector<Column_Variant> > Columns;

  Columns columns;
  std::string all_or_distinct;
  size_t top = std::numeric_limits<size_t>::max ();
  std::vector<Table_Reference> tables;
  Where where;
  Group_By group_by;
  Order_By order_by;
  Having having;

  bool empty () const
  {
    /// I think that it is an error for a query to be empty.
    return tables.empty ();
  }
};
}

namespace
{
class Query_Specification_Columns_Visitor
    : public boost::static_visitor<std::ostream &>
{
public:
  std::ostream &os;
  Query_Specification_Columns_Visitor (std::ostream &OS) : os (OS) {}
  Query_Specification_Columns_Visitor () = delete;

  std::ostream &operator()(const std::string &s) const { return os << s; }

  std::ostream &operator()(
      const std::vector<ADQL::Query_Specification::Column_Variant> &s) const
  {
    auto o = s.begin ();
    if (o != s.end ())
      {
        os << *o;
        ++o;
      }
    for (; o != s.end (); ++o)
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
  auto table = tables.begin ();
  if (table != tables.end ())
    {
      os << *table;
      // os << table->name;
      ++table;
    }
  for (; table != tables.end (); ++table)
    os << ", " << *table;
  // os << ", " << table->name;
  return os;
}

inline std::ostream &
operator<<(std::ostream &os, const ADQL::Query_Specification::Columns &columns)
{
  return boost::apply_visitor (Query_Specification_Columns_Visitor (os),
                               columns);
}

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Query_Specification &query)
{
  os << "SELECT " << query.all_or_distinct
     << (query.all_or_distinct.empty () ? "" : " ")
     << (query.top != std::numeric_limits<unsigned long long>::max ()
             ? "TOP " + std::to_string (query.top) + " "
             : "") << query.columns << " FROM " << query.tables;
  if (!query.where.empty ())
    os << " WHERE " << query.where;
  if (!query.group_by.empty ())
    os << " GROUP BY " << query.group_by;
  if (!query.having.empty ())
    os << " HAVING " << query.having;
  if (!query.order_by.empty ())
    os << " ORDER BY " << query.order_by;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (
    ADQL::Query_Specification,
    (std::string,
     all_or_distinct)(size_t, top)(ADQL::Query_Specification::Columns,
                                   columns)(std::vector<ADQL::Table_Reference>,
                                            tables)(ADQL::Where, where)(
        ADQL::Group_By, group_by)(ADQL::Having, having)(ADQL::Order_By,
                                                        order_by))
