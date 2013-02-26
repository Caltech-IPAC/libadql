#include "Query.hxx"

int main()
{
  ADQL::Query("POINT('foo',10 20)");
  ADQL::Query("POINT('foo',10, 20)");
  ADQL::Query("POINT('foo',10 ,20)");
  ADQL::Query("SELECT ra1,dec2,flux FROM mytable WHERE CONTAINS(POINT('J2000',+10 , -20),CIRCLE('J2000',10 , 20,-1))");
  ADQL::Query("SELECT ra1,dec2,flux FROM mytable WHERE CONTAINS(POINT('J2000',+10 , +20),CIRCLE('J2000',10 , 20,-1))");
  ADQL::Query("SELECT ra1,dec2,flux FROM mytable WHERE CONTAINS(POINT('J2000',mytable.ra,dec),CIRCLE('J2000',+10 , -20,-1))");
  ADQL::Query("SELECT FROM WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , 20,1))");
}
