#include "../Search_Condition.hxx"

std::string ADQL::Search_Condition::string() const
{
  std::stringstream ss;
  ss << *this;
  return ss.str();
}
