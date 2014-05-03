#include <stdexcept>
#include <iostream>
#include "../src/Query.hxx"

int main (int argc, char *argv[])
{
  bool quiet(argc>1 && argv[1]==std::string("-q"));
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
    "And (x<1)",
    "SELECT * FROM my_table1 WHERE (x!=3) and "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1))",
    "SELECT * FROM my_table1 WHERE x!=3",
    "SELECT * FROM my_table1",
    "SELECT * FROM my_table1 where x>2",
    "SELECT * FROM my_table1 where x>2 AND x<4",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And (x<1 And x>2 Or y < 3 Or y >5)",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And (x<1 And x>2)",
    "SELECT * FROM my_table1 where (x>2 AND x<4) Or (x>6 and x<10)",
    "SELECT * FROM my_table1 where (x Between 2 AND 4) Or (x>6 and x<10)",
    "SELECT * FROM fp_psc WHERE CONTAINS(POINT('J2000',fp_psc.ra,fp_psc.dec),"
    "CIRCLE('J2000',1,1,0.08))=1 and (ra between 0.95 and 1.05)",
    // "SELECT * FROM my_table1 where x in (select y from my_table2)",
    "SELECT * FROM my_table1 where x in (10,20,30)",
    "SELECT * FROM my_table1 where x not in (10,20,30)",
    "SELECT All * FROM my_table1",
    "SELECT Distinct * FROM my_table1",
    "SELECT Top 50 * FROM my_table1",
    "SELECT * FROM my_table1 where 38*(x+1-3)>2/4",
    "SELECT ra+dec as ra_dec FROM my_table1",
    "SELECT ra+dec FROM my_table1",
    "SELECT my_tablel1.* FROM my_table1",
    "SELECT sin(dec),cos(dec),tan(dec),cot(dec),asin(dec),acos(dec),"
    "atan(dec),atan2(ra,dec) FROM my_table1",
    "SELECT abs(ra),ceiling(ra), degrees(ra),exp(ra),floor(ra),log(ra),log10(ra),"
    "radians(ra),sqrt(ra) FROM my_table1",
    "SELECT mod(ra, dec),power( ra,dec ),pi(),rand(ra),rand(),"
    "round(ra,10),round(ra),truncate(ra),truncate(ra,10) FROM my_table1",
    "SELECT modern() FROM my_table1",
    "SELECT my_modern_function(ra,dec) FROM my_table1",
    "SELECT my_modern_function(ra,dec), modern() FROM my_table1",
    "select 'a b c','a','a ''bv' from b",
    "select \"a b\",\"a \"\" b\" from b",
    "select 'a' 'b' from b",
    "select 'a' --This is a useful comment\n 'b' from b",
    "select (a), sum(a), max(all a), min(distinct a), count(a), avg ( a ) ,"
    "min(a) from a",
    "select max(all a) from a",
    "select count ( * ) from a",
    "select count(*) from a",
    "select count(a) from a",
    "select count(all a) from a",
    "select count(distinct a) from a",
    "select sum(a) from a",
    "select sum(all a) from a",
    "select sum(DISTINCT a) from a",
    "select sum(DISTINCTa) from a",
    "select single from a",
    "select a,b from a group by a",
    "select a,b from a group by a having x>2",
    "SELECT * FROM my_table1 where x in(10,20,30)",
    "SELECT * FROM my_table1 where x not in(10,20,30)",
    "SELECT * FROM my_table1 order by x",
    "SELECT * FROM my_table1 order by x asc",
    "SELECT * FROM my_table1 order by x desc",
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
    "1 = CONTAINS(POINT('J2000',dec,dec),CIRCLE('J2000',+10 , -20,-1))",
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And x<1 And x>2 Or y < 3 Or y >5"
    "SELECT *,ra FROM my_table1",
    "SELECT my_tablel1.* as ra_dec FROM my_table1",
    "SELECT sin as ra_dec FROM my_table1",
    "select sum(a,b) from a",
    "select abs(a,b) from a",
    "select a,b from a groupby a",
    "select a asb from a groupby a",
    "SELECT * FROM my_table1 where (x notBetween 2 AND 4)",
    "SELECT * FROM my_table1 where x notin (10,20,30)",
    "SELECT * FROM mytable WHERE"
    "CONTAINS(POINT('J2000',mytable.ra,dec),CIRCLE('J2000',+10 , -20,-1)) = 1",
  };

  int result(0);
  for (auto &i : pass)
    {
      try
        {
          ADQL::Query query (i);
          if(!quiet)
            {
              std::cout << "PASS: " << i << "\n";
              std::cout << "SELECT "
                        << query.all_or_distinct
                        << (query.all_or_distinct.empty() ? "" : " ")
                        << (query.top!=std::numeric_limits<unsigned long long>::max()
                            ? "TOP " + std::to_string(query.top) + " " : "")
                        << query.columns
                        << " FROM " << query.table;
              if(query.where.search_condition.good())
                std::cout << " WHERE " << query.where.search_condition;
              std::cout << "\n";
            }
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
          if(!quiet)
            std::cout << "PASS: " << i << "\n";
        }
    }

  return result;
}
