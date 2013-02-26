#ifndef ADQL_GEOMETRY_HXX
#define ADQL_GEOMETRY_HXX

#include "Geometry/Contains.hxx"

namespace ADQL
{
  class Geometry
  {
  public:
    Contains contains;
  };
}

BOOST_FUSION_ADAPT_STRUCT(ADQL::Geometry,
                          (ADQL::Contains, contains))

#endif
