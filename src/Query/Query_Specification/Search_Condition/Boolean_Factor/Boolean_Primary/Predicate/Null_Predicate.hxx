#pragma once

namespace ADQL
{
class Null_Predicate
{
public:
  std::string column;
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
                           (std::string, column)(std::string, Not))
