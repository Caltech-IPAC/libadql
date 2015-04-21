#pragma once

namespace ADQL
{
class Like_Predicate
{
public:
  std::string match, pattern;
  std::string Not;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Like_Predicate &c)
{
  return os << c.match << " " << c.Not << (c.Not.empty () ? "" : " ")
            << "LIKE " << c.pattern;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Like_Predicate,
                           (std::string, match)(std::string, Not)(std::string,
                                                                  pattern))
