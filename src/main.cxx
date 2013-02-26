#include "Query.hxx"

int main()
{
  ADQL::Query("POINT('foo',10 20)");
  ADQL::Query("POINT('foo',10, 20)");
  ADQL::Query("POINT('foo',10 ,20)");
  ADQL::Query("CONTAINS(POINT('foo',10 , 20),CIRCLE('foo',10 , 20,1))");
}
