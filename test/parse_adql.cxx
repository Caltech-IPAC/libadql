#include <stdexcept>
#include <iostream>
#include "../src/Query.hxx"

int main ()
{
  std::vector<std::string> pass = {
    "Select ra1,dec2,flux From mytable Where "
    "Contains(Point('j2000',ra,dec),Circle('J2000',+10 , -20,-1))= 1",
    "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000 Geocenter',ra,dec),CIRCLE('J2000',+10 , -20,-1))= 1",
    "SELECT * FROM mytable WHERE "
    "CONTAINS(POINT('J2000',mytable.ra,dec),CIRCLE('J2000',+10 , -20,-1)) = 1",
    "SELECT * FROM my_table WHERE "
    "1=CONTAINS(POINT('J2000',ra,my_table.dec),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And x<1",
    "SELECT * FROM my_table1 WHERE x!=3 and "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) ",
    "SELECT * FROM my_table1",
    "SELECT * FROM my_table1 where x>2",
    "SELECT * FROM my_table1 where x>2 AND x<4",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And x<1 And x>2 Or y < 3 Or y >5",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And (x<1 And x>2)",
    "SELECT * FROM my_table1 where (x>2 AND x<4) Or (x>6 and x<10)",
    "SELECT * FROM my_table1 where (x Between 2 AND 4) Or (x>6 and x<10)",
    "SELECT * FROM fp_psc WHERE CONTAINS(POINT('J2000',fp_psc.ra,fp_psc.dec),"
    "CIRCLE('J2000',1,1,0.08))=1 and ra between 0.95 and 1.05",
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
          std::cout << "SELECT " << query.output_columns_string()
                    << " FROM " << query.table;
          if(query.where.search_condition.good())
            std::cout << " WHERE " << query.where.search_condition;
          std::cout << "\n";
        }
      catch (std::runtime_error &e)
        {
          std::cout << "FAIL: " << i << "\n";
          std::cout << e.what() << "\n";
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
