#include "../Array_Constructor.hxx"
#include "../../Value_Expression.hxx"

namespace ADQL
{
std::ostream &
operator<<(std::ostream &os,
           const ADQL::Array_Constructor &array_constructor)
{
  os << "ARRAY[";
  for (auto v=array_constructor.values.begin ();
       v!=array_constructor.values.end ();)
    {
      os << *v;
      ++v;
      if (v!=array_constructor.values.end ())
        {
          os << ',';
        }
    }
  os << ']';
  return os;
}
}
