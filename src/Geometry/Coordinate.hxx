#ifndef ADQL_COORDINATE_HXX
#define ADQL_COORDINATE_HXX

#include "boost/variant.hpp"
#include <boost/fusion/include/adapt_struct.hpp>


namespace ADQL
{
  typedef boost::variant<double,std::string> number_variant;

  struct Coordinate
  {
  public:
    number_variant ra, dec;
  };
}

BOOST_FUSION_ADAPT_STRUCT(ADQL::Coordinate,
                          (ADQL::number_variant, ra)
                          (ADQL::number_variant, dec))

#endif
