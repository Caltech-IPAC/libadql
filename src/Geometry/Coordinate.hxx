#ifndef ADQL_COORDINATE_HXX
#define ADQL_COORDINATE_HXX

#include "boost/variant.hpp"
#include <boost/fusion/include/adapt_struct.hpp>
#include <sstream>

namespace ADQL
{
  typedef boost::variant<double,std::string> number_variant;

  struct Coordinate
  {
  public:
    number_variant numbers[2];
    std::string ra() const
    {
      return ra_dec(0);
    }
    std::string dec() const
    {
      return ra_dec(1);
    }
    std::string ra_dec(const int &i) const
    {
      std::stringstream ss;
      ss << numbers[i];
      return ss.str();
    }
  };
}

BOOST_FUSION_ADAPT_STRUCT(ADQL::Coordinate,
                          (ADQL::number_variant, numbers[0])
                          (ADQL::number_variant, numbers[1]))

#endif
