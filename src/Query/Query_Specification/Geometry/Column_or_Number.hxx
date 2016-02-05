#pragma once

#include <string>
#include <stdexcept>

#include <boost/variant.hpp>

#include "../../../to_string.hxx"
#include "../Column_Reference.hxx"

namespace ADQL
{
typedef boost::variant<Column_Reference, double> Column_or_Number;

class Column_or_Number_empty_Visitor : public boost::static_visitor<bool>
{
public:
  bool operator () (const double &) const
  {
    return false;
  }
  bool operator () (const Column_Reference &s) const
  {
    return s.empty ();
  }
};

class Column_or_Number_double_Visitor
  : public boost::static_visitor<double>
{
public:
  double operator () (const double &p) const
  {
    return p;
  }
  double operator () (const Column_Reference &c) const
  {
    throw std::runtime_error ("Expected a number, but got: "
                              + ADQL::to_string (c));
    return 0;
  }
};

inline double double_or_throw (const Column_or_Number &c)
{
  Column_or_Number_double_Visitor visitor;
  return boost::apply_visitor (visitor, c);
}
}
