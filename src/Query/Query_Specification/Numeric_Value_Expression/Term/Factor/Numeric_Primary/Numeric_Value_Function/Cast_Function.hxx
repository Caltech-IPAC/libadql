#pragma once

#include "../../../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class Cast_Function
{
public:
  Value_Expression_Wrap expression;
  std::string as;
  bool empty () const { return as.empty (); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Cast_Function &cast_function)
{
  return os << "CAST(" << cast_function.expression << " AS "
            << cast_function.as << ")";
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Cast_Function,
                           (ADQL::Value_Expression_Wrap,
                            expression)(std::string, as))
