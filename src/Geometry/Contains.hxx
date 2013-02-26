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

#endif
