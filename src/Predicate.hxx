#pragma once

#include "Where/Comparison.hxx"

namespace ADQL
{
class Constraints
{
public:
  Comparison comparison;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Where, (ADQL::Comparison, comparison))

