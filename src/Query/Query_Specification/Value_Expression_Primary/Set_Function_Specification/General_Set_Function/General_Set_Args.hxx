#pragma once

#include "../../../Value_Expression_Wrap.hxx"
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class General_Set_Args
{
public:
  std::string set_quantifier;
  Value_Expression_Wrap wrap;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::General_Set_Args &general_set_args)
{
  if (!general_set_args.set_quantifier.empty ())
    {
      os << general_set_args.set_quantifier << ' ';
    }
  os << general_set_args.wrap;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::General_Set_Args,
                           (std::string,
                            set_quantifier)(ADQL::Value_Expression_Wrap, wrap))
