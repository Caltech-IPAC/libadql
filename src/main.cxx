#include "Query.hxx"

int main()
{
  ADQL::Query("10 20");
  ADQL::Query("10, 20");
  ADQL::Query("10 ,20");
  ADQL::Query("10 , 20");
}
