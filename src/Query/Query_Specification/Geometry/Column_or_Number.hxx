#pragma once

#include <string>

#include <boost/variant.hpp>

namespace ADQL
{
typedef boost::variant<std::string, double> Column_or_Number;

class Column_or_Number_empty_Visitor : public boost::static_visitor<bool>
{
public:
  bool operator () (const double &) const
  {
    return false;
  }
  bool operator () (const std::string &s) const
  {
    return s.empty ();
  }
};


}
