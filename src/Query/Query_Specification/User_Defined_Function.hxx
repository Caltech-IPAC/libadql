#pragma once

#include "Value_Expression.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <iostream>

namespace ADQL
{
class User_Defined_Function
{
public:
  std::string function;
  std::vector<ADQL::Value_Expression> args;
  bool empty () const { return function.empty (); }
};

inline std::ostream &
operator<<(std::ostream &os,
           const ADQL::User_Defined_Function &user_defined_function)
{
  os << user_defined_function.function << '(';
  for (auto a = user_defined_function.args.begin ();
       a != user_defined_function.args.end ();)
    {
      os << *a;
      ++a;
      if (a != user_defined_function.args.end ())
        {
          os << ',';
        }
    }
  os << ')';
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::User_Defined_Function,
                           (std::string,
                            function)(std::vector<ADQL::Value_Expression>,
                                      args))
