#pragma once

#include "Geometry/Contains.hxx"
#include "Geometry/Intersects.hxx"

namespace
{
class Geometry_Predicate_Shape_Visitor : public boost::static_visitor<const ADQL::Shape &>
{
public:
  const ADQL::Shape &operator()(const ADQL::Intersects &s) const
  {
    return s.shape;
  }
  const ADQL::Shape &operator()(const ADQL::Contains &s) const
  {
    return s.shape;
  }
};
}

namespace ADQL
{
class Geometry
{
public:
  typedef boost::variant<Intersects, Contains> Predicate;
  Predicate predicate;
  bool empty () const { return empty_variant (predicate); }
  const Shape &shape() const
  {
    Geometry_Predicate_Shape_Visitor visitor;
    return boost::apply_visitor (visitor, predicate);
  }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Geometry& geometry)
{
  if(!geometry.empty())
    os << geometry.predicate;
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Geometry, (ADQL::Geometry::Predicate, predicate))
