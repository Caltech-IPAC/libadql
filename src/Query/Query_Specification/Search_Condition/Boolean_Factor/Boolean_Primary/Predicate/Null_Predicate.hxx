#pragma once

namespace ADQL
{
class Null_Predicate
{
public:
  Value_Expression column;
  std::string Not;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Null_Predicate &c)
{
  return os << c.column << " IS " << c.Not << (c.Not.empty () ? "" : " ")
            << "NULL";
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Null_Predicate,
                           (ADQL::Value_Expression, column)(std::string, Not))
