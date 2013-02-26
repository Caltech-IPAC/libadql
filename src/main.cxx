#include "Query.hxx"

int main()
{
  ADQL::Query("POINT('foo',10 20)");
  ADQL::Query("POINT('foo',10, 20)");
  ADQL::Query("POINT('foo',10 ,20)");
  ADQL::Query("SELECT ra,dec FROM mytable WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , 20,1))");
  ADQL::Query("SELECT FROM WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , 20,1))");
}
