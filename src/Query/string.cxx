#include "../Query.hxx"

std::string ADQL::Query::string() const
{
  std::stringstream ss;
  ss << *this;
  return ss.str();
}
