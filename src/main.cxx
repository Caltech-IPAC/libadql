#include <stdexcept>
#include <iostream>
#include "Query.hxx"

int main ()
{
  std::vector<std::string> inputs = {
    "POINT('foo',10 20)", "POINT('foo',1.0, 20)", "POINT('foo',10 ,-2.0)",
    "SELECT ra1,dec2,flux FROM mytable WHERE CONTAINS(POINT('J2000',+1.0 , "
    "-20),CIRCLE('J2000',-.10 , +.20,-1))=1",
    "SELECT ra1,dec2,flux FROM mytable WHERE CONTAINS(POINT('J2000',+10 , "
    "+2.0),CIRCLE('J2000',.10 , -0.20,-1)) =1",
    "SELECT ra1,dec2,flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000',ra,dec),CIRCLE('J2000',+10 , -20,-1))= 1",
    "SELECT * FROM mytable WHERE "
    "CONTAINS(POINT('J2000',mytable.ra,dec),CIRCLE('J2000',+10 , -20,-1)) = 1",
    "SELECT * FROM my_table WHERE "
    "1=CONTAINS(POINT('J2000',ra,my_table.dec),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT FROM WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , "
    "20,1))",
    "SELECT * FROM mytable WHERE "
    "1 =CONTAINS(POINT('J2000',ra,ra),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT * FROM mytable WHERE "
    "1 = CONTAINS(POINT('J2000',dec,dec),CIRCLE('J2000',+10 , -20,-1))"
  };

  for (auto &i : inputs)
    {
      try
      {
        ADQL::Query query (i);
        std::cout << "Query: " << i << "\n"
                  << "  Output Columns:";
        for (auto &o : query.output_columns)
          {
            std::cout << " " << o;
          }
        std::cout << "\n  Table: " << query.table << "\n"
                  << "  Contains:\n"
                  << "    Point: " << query.geometry.contains.point.coord_sys
                  << " " << query.geometry.contains.point.coordinate.ra ()
                  << " " << query.geometry.contains.point.coordinate.dec ()
                  << "\n"
                  << "    Circle: " << query.geometry.contains.circle.coord_sys
                  << " " << query.geometry.contains.circle.coordinate.ra ()
                  << " " << query.geometry.contains.circle.coordinate.dec ()
                  << " " << query.geometry.contains.circle.radius << "\n";
      }
      catch (std::runtime_error &e)
      {
        std::cerr << "Invalid input: " << e.what () << " " << i << "\n";
      }
    }
}
