#pragma once

#include "../../../Result.hxx"

namespace ADQL
{
class Simple_When
{
public:
  std::string when;
  Result result;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Simple_When &simple_when)
{
  return os << "WHEN " << simple_when.when << " "
            << "THEN " << simple_when.result;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Simple_When,
                           (std::string, when)(ADQL::Result, result))
