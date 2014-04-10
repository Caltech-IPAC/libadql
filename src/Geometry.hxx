#pragma once

#include "Geometry/Contains.hxx"

namespace ADQL
{
class Geometry
{
public:
  Contains contains;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Geometry, (ADQL::Contains, contains))

