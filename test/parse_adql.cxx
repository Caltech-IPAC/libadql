#include <stdexcept>
#include <iostream>
#include "../src/Query.hxx"

int main ()
{
  std::vector<std::string> pass = {
    "SELECT ra1,dec2,flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000',ra,dec),CIRCLE('J2000',+10 , -20,-1))= 1",
    "SELECT * FROM mytable WHERE "
    "CONTAINS(POINT('J2000',mytable.ra,dec),CIRCLE('J2000',+10 , -20,-1)) = 1",
    "SELECT * FROM my_table WHERE "
    "1=CONTAINS(POINT('J2000',ra,my_table.dec),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1))"
  };


  std::vector<std::string> fail = {
    "POINT('foo',10 20)", "POINT('foo',1.0, 20)", "POINT('foo',10 ,-2.0)",
    "SELECT ra1,dec2,flux FROM mytable WHERE CONTAINS(POINT('J2000',+1.0 , "
    "-20),CIRCLE('J2000',-.10 , +.20,-1))=1",
    "SELECT ra1,dec2,flux FROM mytable WHERE CONTAINS(POINT('J2000',+10 , "
    "+2.0),CIRCLE('J2000',.10 , -0.20,-1)) =1",
    "SELECT FROM WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , "
    "20,1))",
    "SELECT * FROM mytable WHERE "
    "1 =CONTAINS(POINT('J2000',ra,ra),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT * FROM mytable WHERE "
    "1 = CONTAINS(POINT('J2000',dec,dec),CIRCLE('J2000',+10 , -20,-1))"
  };

  int result(0);
  for (auto &i : pass)
    {
      try
        {
          ADQL::Query query (i);
          std::cout << "PASS: " << i << "\n";
        }
      catch (std::runtime_error &e)
        {
          std::cout << "FAIL: " << i << "\n";
          result=1;
        }
    }


  for (auto &i : fail)
    {
      try
        {
          ADQL::Query query (i);
          std::cout << "FAIL: Unexpected parse: " << i << "\n";
          result=1;
        }
      catch (std::runtime_error &e)
        {
          std::cout << "PASS: " << i << "\n";
        }
    }

  return result;
}
