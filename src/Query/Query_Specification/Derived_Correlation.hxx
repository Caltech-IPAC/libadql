#pragma once

#include "../Subquery.hxx"

namespace ADQL
{
class Derived_Correlation
{
public:
  ADQL::Subquery subquery;
  std::string as;
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Derived_Correlation &d)
{
  os << d.subquery;
  if (!d.as.empty ())
    os << " AS " << d.as;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Derived_Correlation,
                           (ADQL::Subquery, subquery)(std::string, as))
