#ifndef ADQL_CONTAINS_HXX
#define ADQL_CONTAINS_HXX

#include "Point.hxx"
#include "Circle.hxx"

namespace ADQL
{
  class Contains
  {
  public:
    Point point;
    Circle circle;
  };
}

BOOST_FUSION_ADAPT_STRUCT(ADQL::Contains,
                          (ADQL::Point, point)
                          (ADQL::Circle, circle))

#endif
