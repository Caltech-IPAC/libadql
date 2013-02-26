#include "Query.hxx"

int main()
{
  ADQL::Query("POINT('foo',10 20)");
  ADQL::Query("POINT('foo',10, 20)");
  ADQL::Query("POINT('foo',10 ,20)");
  ADQL::Query("CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , 20,1))");
}
