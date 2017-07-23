#pragma once

#include "Numeric_Primary/Numeric_Value_Function.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Numeric_Primary
{
public:
  typedef boost::variant<std::string, Numeric_Value_Function> Variant;
  Variant variant;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Numeric_Primary &numeric_primary)
{
  return os << numeric_primary.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Numeric_Primary,
                           (ADQL::Numeric_Primary::Variant, variant))
