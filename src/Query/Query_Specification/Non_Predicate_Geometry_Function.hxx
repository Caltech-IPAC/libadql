#pragma once
#include "Geometry/Contains.hxx"
namespace ADQL
{
    class Non_Predicate_Geometry_Function
{
public:
    std::string function;
    ADQL::Contains::Point_or_Column arg;
  bool empty () const { return function.empty (); }
};


inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Non_Predicate_Geometry_Function &non_predicate_geometry_function)
{
  if (!non_predicate_geometry_function.empty ())
      return os << non_predicate_geometry_function.function << "(" << non_predicate_geometry_function.arg << ")";
  return os;
}
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Non_Predicate_Geometry_Function,
                           (std::string, function)
                           (ADQL::Contains::Point_or_Column, arg))

