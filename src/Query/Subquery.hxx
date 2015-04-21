#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant/variant.hpp>

#include "Query_Specification_Wrap.hxx"
#include "Query_Specification/Joined_Table_Wrap.hxx"

namespace ADQL
{
class Subquery
{
public:
  typedef boost::variant<Joined_Table_Wrap,Query_Specification_Wrap> Variant;
  Variant variant;
  bool empty () const;
};
std::ostream &operator<<(std::ostream &os, const Subquery &subquery);
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Subquery,
                           (ADQL::Subquery::Variant, variant))
