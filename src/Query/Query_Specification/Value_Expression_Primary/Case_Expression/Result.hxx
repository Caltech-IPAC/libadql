#pragma once

#include "../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>

#include <boost/variant.hpp>

namespace ADQL
{
class Result
{
public:
  typedef boost::variant<std::string, Value_Expression_Wrap> Variant;
  Variant variant;
  bool empty () const;
};

std::ostream &operator<<(std::ostream &os, const ADQL::Result &result);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Result,
                           (ADQL::Result::Variant, variant))
