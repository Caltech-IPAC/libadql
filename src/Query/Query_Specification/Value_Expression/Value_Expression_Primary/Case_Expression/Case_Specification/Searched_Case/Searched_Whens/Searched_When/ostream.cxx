#include "../Searched_When.hxx"
#include "../../../../../../../Search_Condition.hxx"


namespace ADQL
{
std::ostream &operator<<(std::ostream &os,
                         const ADQL::Searched_When &searched_when)
{
  return os << "WHEN " << searched_when.wrap << " THEN "
            << searched_when.result;
}
}
