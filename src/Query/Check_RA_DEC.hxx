#pragma once

#include "boost/variant.hpp"

class Check_RA_DEC : public boost::static_visitor<bool>
{
  std::string table, ra_dec;

public:
  Check_RA_DEC (const std::string &Table, const std::string &Ra_dec)
      : table (Table), ra_dec (Ra_dec)
  {
  }
  bool operator()(const double &) const { return false; }
  bool operator()(const std::string &s) const
  {
    return s == ra_dec || s == table + "." + ra_dec;
  }
};
