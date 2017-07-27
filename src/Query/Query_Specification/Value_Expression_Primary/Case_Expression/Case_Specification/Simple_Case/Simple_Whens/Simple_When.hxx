#pragma once

#include "../../../Result.hxx"

namespace ADQL
{
class Simple_When
{
public:
  Value_Expression_Wrap wrap;
  Result result;
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Simple_When &simple_when);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Simple_When, (ADQL::Value_Expression_Wrap,
                                               wrap)(ADQL::Result, result))
