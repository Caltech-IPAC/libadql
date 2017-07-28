#pragma once

#include "Numeric_Value_Expression.hxx"
#include "String_Value_Expression.hxx"

#include <boost/variant.hpp>

namespace ADQL
{
class Value_Expression_Non_Bool
{
public:
  typedef boost::variant<Numeric_Value_Expression, String_Value_Expression>
      Variant;
  Variant variant;
  bool empty () const { return empty_variant (variant); }
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::Value_Expression_Non_Bool &value_expression_non_bool)
{
  return os << value_expression_non_bool.variant;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Value_Expression_Non_Bool,
                           (ADQL::Value_Expression_Non_Bool::Variant, variant))
