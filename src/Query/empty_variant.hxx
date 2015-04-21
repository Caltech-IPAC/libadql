#pragma once

namespace
{
class Empty_Visitor: public boost::static_visitor<bool>
{
public:
  template <class T>
  bool operator()(const T &s) const
  {
    return s.empty ();
  }
};
}

namespace ADQL
{
template <class T>
bool empty_variant (const T& variant)
{
  Empty_Visitor visitor;
  return boost::apply_visitor (visitor, variant);
}
}
