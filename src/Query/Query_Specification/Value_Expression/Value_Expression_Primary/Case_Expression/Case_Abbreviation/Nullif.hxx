#pragma once

#include "../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

namespace ADQL
{
class Nullif
{
public:
  Value_Expression_Wrap arg0, arg1;
  bool empty () const;
};

std::ostream &operator<<(std::ostream &os, const ADQL::Nullif &nullif);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Nullif,
                           (ADQL::Value_Expression_Wrap,
                            arg0)(ADQL::Value_Expression_Wrap, arg1))
