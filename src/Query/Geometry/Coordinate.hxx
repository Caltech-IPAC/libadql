#pragma once

#include <vector>
#include <sstream>
#include <boost/fusion/include/adapt_struct.hpp>
#include "../Number_Variant.hxx"

namespace ADQL
{
struct Coordinate
{
public:
  std::vector<Number_Variant> numbers;
  Coordinate(): numbers(2) {}
  std::string ra () const { return ra_dec (0); }
  std::string dec () const { return ra_dec (1); }
  std::string ra_dec (const int &i) const
  {
    std::stringstream ss;
    ss << numbers[i];
    return ss.str ();
  }
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Coordinate,
                           (ADQL::Number_Variant,
                            numbers[0])(ADQL::Number_Variant, numbers[1]))

