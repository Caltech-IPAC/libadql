#include <map>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "../src/Query.hxx"

int main (int argc, char *argv[])
{
  bool quiet(argc>1 && argv[1]==std::string("-q"));
  std::vector<std::string> pass = {
    "Select ra1,dec2,flux From mytable Where "
    "Contains(Point('j2000',ra,dec),Circle('J2000',+10 , -20,-1))= 1",
    "Select ra1,dec2,flux From mytable Where "
    "Contains(Point('j2000',ra,dec),Circle('J2000',+10 , -20,-1))",
    "Select ra1,dec2,flux From mytable Where "
    "Contains(pos,Circle('J2000',+10 , -20,-1))",
    "Select ra1,dec2,flux From mytable Where "
    "Intersects(pos,Circle('J2000',+10 , -20,-1))= 1",
    "Select ra1,dec2,flux From mytable Where "
    "INTERSECTs(pos,Circle('J2000',+10 , -20,-1))",
    "Select ra1,dec2,flux From mytable Where "
    "Contains(Point('galactic',ra,dec),Circle('galactic',+10 , -20,-1))= 1",
    "Select ra1,dec2,flux From mytable Where "
    "Contains(Point('ICRS',ra,dec),Circle('icrs',+10 , -20,-1))= 1",
    "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000 Geocenter',ra,dec),CIRCLE('J2000 Geocenter',+10 , -20,-1))= 1",
    "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000 Geocenter',ra,dec),BOX('J2000',+10 , -20,1,2))= 1",
    "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000 Geocenter',ra,dec),ELLIPSE('J2000',+10 , -20,1,2,3))= 1",
    "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000 Geocenter',ra,dec),ELLIPSE(+10 , -20,1,2,3))",
    "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000 Geocenter',ra,dec),POLYGON('J2000',0,1,2,3,4,5,6,7,8,9,10,11,12,13))= 1",
    "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
    "CONTAINS(POINT('J2000 Geocenter',ra,dec),POLYGON(0,1,2,3,4,5,6,7,8,9,10,11,12,13))",
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
    "1= CONTAINS(POINT(my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And (x<1 And x>2 Or y < 3 Or y >5)",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And (x<1 And x>2)",
    "SELECT * FROM my_table1 where (x>2 AND x<4) Or (x>6 and x<10)",
    "SELECT * FROM my_table1 where (x Between 2 AND 4) Or (x>6 and x<10)",
    "SELECT * FROM my_table1 where x is null",
    "SELECT * FROM my_table1 where x is not null",
    "SELECT * FROM fp_psc WHERE CONTAINS(POINT('J2000',ccc.fp_psc.ra, aaa.ccc.fp_pscdec),"
    "CIRCLE(1,1,0.08))=1 and (ra between 0.95 and 1.05)",
    "SELECT * FROM my_table1 where x in (select y from my_table2)",
    "SELECT * FROM my_table1 where x in (10,20,30)",
    "SELECT * FROM my_table1 where x not in (10,20,30)",
    "SELECT All * FROM my_table1",
    "SELECT Distinct * FROM my_table1",
    "SELECT Top 14223 * FROM my_table1",
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
    "SELECT my_modern_function(ra,dec) || modern() FROM my_table1",
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
    "SELECT * FROM my_table1 order by x",
    "SELECT * FROM my_table1 order by x asc",
    "SELECT * FROM my_table1 order by x desc",
    "select b from a where x<1 order by a",
    "SELECT * FROM my_table1 where x like y",
    "SELECT * FROM my_table1 where x like y || z",
    "SELECT * FROM my_table1 where x not like my_sin(x)",
    "SELECT * FROM my_table1 where x like my_sin(x) || x",
    "SELECT * FROM my_table1 where exists (select a from b)",
    "SELECT * FROM my_table WHERE (mjd>=55550.0 and mjd<=65650.5)",
    "SELECT my_table1.*,'table' from my_table1",
    "SELECT myschema.mytable.* from myschema.mytable",
    "SELECT * from mycatalog.myschema.mytable",
    "SELECT * from myschema.mytable",
    "SELECT mycatalog.myschema.mytable.* from mycatalog.myschema.mytable",
    "SELECT * from myschema.mytable as mine",
    "SELECT * from myschema.mytable mine",
    "SELECT * from myschema.mytable, yourscheme.yourtable mine",
    "SELECT * from TAP_UPLOAD.mytable",
    "SELECT * from tapmod.mytable",
    "SELECT TAP_UPLOAD.mytable.b from TAP_UPLOAD.mytable",
    "SELECT TAP_UPLOAD.mytable.* from TAP_UPLOAD.mytable",
    "SELECT TAP_UPLOAD.mytable.*, fp_psc.* from TAP_UPLOAD.mytable, fp_psc",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',TAP_UPLOAD.mytable.ra,TAP_UPLOAD.mytable.dec),"
    "CIRCLE('J2000',+10 , -20,-1)) ",
    "SELECT * FROM my_table1 WHERE "
    "1= CONTAINS(POINT('J2000',TAP_UPLOAD.mytable.ra,TAP_UPLOAD.mytable.dec),"
    "CIRCLE('J2000',TAP_UPLOAD.mytable.ra,TAP_UPLOAD.mytable.dec,-1)) ",
    "SELECT alligator from a",
    "SELECT tophat from a",
    "SELECT max(alligator) from a",
    "SELECT maximus from a",
    "SELECT ast from a",
    "Select fromage from fromming",
    "Select fromage from fromming ast",
    "select alligator from table1 join table2",
    "select alligator from table1 natural join table2",
    "select alligator from table1 natural left outer join table2",
    "select alligator from table1 right outer join table2",
    "select alligator from table1 right join table2",
    "select alligator from table1 full outer join table2",
    "select alligator from table1 natural inner join table2",
    "select alligator from table1 inner join table2",
    "select alligator from (table1 join table2)",
    "select alligator from table1 join (table2 join (table3 join table4))",
    "select alligator from table1 join table2 on a=b",
    "select alligator from table1 t1 join table2 t2 on a=b join table3 t3 on c=d join table4 t4 on e=f join table5 t5 on g=h",
    "select alligator from (table1 t1 join table2 t2 on a=b) join table3 t3 on c=d",
    "select alligator from table1 join table2 using (a,b, c )",
    "select TOP 14223 caom.observation.*,caom.plane.*,caom.artifact.*,caom.part.*,caom.chunk.* FROM caom.observation join caom.plane on caom.observation.obsid = caom.plane.obsid join caom.artifact on caom.plane.planeid = caom.artifact.planeid join caom.part on caom.artifact.artifactid = caom.part.artifactid join caom.chunk on caom.part.partid = caom.chunk.partid",
    "select TOP 14223 caom.observation.*,caom.plane.*,caom.artifact.*,caom.part.*,caom.chunk.* FROM (((caom.observation join caom.plane on caom.observation.obsid = caom.plane.obsid) join caom.artifact on caom.plane.planeid = caom.artifact.planeid) join caom.part on caom.artifact.artifactid = caom.part.artifactid) join caom.chunk on caom.part.partid = caom.chunk.partid",
    "select alligator from (select a from b) as c",
    "select fp_psc.* from fp_psc, TAP_UPLOAD.mytable where "
    "1=contains(fp_psc.ra_dec, "
    "circle('j2000',TAP_UPLOAD.mytable.ra,TAP_UPLOAD.mytable.dec,"
    "0.001))",
    "select fp_psc.* from fp_psc, TAP_UPLOAD.mytable where "
    "1=contains(fp_psc.ra_dec, "
    "circle('j2000',TAP_UPLOAD.mytable.ra,TAP_UPLOAD.mytable.dec,"
    "TAP_UPLOAD.mytable.r))",
    "select fp_psc.* from fp_psc, TAP_UPLOAD.mytable where "
    "1=contains(fp_psc.ra_dec, "
    "circle('j2000',10,TAP_UPLOAD.mytable.dec,"
    "TAP_UPLOAD.mytable.r))",
    "select fp_psc.* from fp_psc, TAP_UPLOAD.mytable where "
    "1=contains(fp_psc.ra_dec, "
    "circle('j2000',TAP_UPLOAD.mytable.ra,10,"
    "TAP_UPLOAD.mytable.r))",
    "select (fp_psc.x * TAP_UPLOAD.mytable.x) as dx from fp_psc, "
    "TAP_UPLOAD.mytable",
    "select (TAP_UPLOAD.mytable.x - fp_psc.x) as dx from TAP_UPLOAD.mytable, "
    "fp_psc",
    "select TAP_UPLOAD.mytable.x - TAP_UPLOAD.mytable.y as dx from TAP_UPLOAD.mytable, "
    "fp_psc",
    "select (fp_psc.x - fp_psc.y) + (TAP_UPLOAD.mytable.x - fp_psc.x) as dxy from fp_psc",
    "select fp_psc.x - TAP_UPLOAD.mytable.x from fp_psc, TAP_UPLOAD.mytable",
    "select TAP_UPLOAD.mytable.x - fp_psc.x from fp_psc, TAP_UPLOAD.mytable",
    "select * from herschel.observations where ST_Covers(poly,ST_Point(10,10))='t' "
    "or ST_Distance(poly,ST_Point(10,10)) <= 0.0",
    "select herschel.observations.*, ST_Distance(ST_Centroid(poly),ST_Point(84.912154,-69.652608)) "
    "as dist_to_centroid"
    " from herschel.observations where ST_Covers(poly,ST_Point(10,10))='t' "
    "or ST_Distance(poly,ST_Point(10,10)) <= 0.0",
    "select * from a where (1=0) AND (2=1) ORDER BY cntr ASC",
    "select '{a,b}' from c",
    "select ARRAY[10,20] from c",
    "select ARRAYNOT from c",
    "select a[b] from c",
    "select ((ARRAY[10,20])[1]) from c",
    "select ARRAY[10,20][1], (ARRAY[10,20])[1],(ARRAY[10,20])[band][pass][info][5] from c",
    "select right(band), left(band,2) from c",
    "select ARRAY[10,20][band] * 1.0e-6 from c",
    "select upper(band), lower(band), trim(band) from c",
    "select mod(cast(foo as numeric),360.0) from c",
    "select * from twomass.full_images where (ST_DWithin(twomass.full_images.poly,ST_Point(1, 1),0*111194.68229846345,'f'))",
    "SELECT schema_name as schemas FROM (select schema_name, min(table_index) as schema_index from TAP_SCHEMA.tables group by schema_name order by schema_index) as temp_schemas group by schemas order by schema_index",
    "select schema_name from (select schema_name, min(table_index) as schema_index from TAP_SCHEMA.tables group by schema_name order by schema_index) temp_schemas",
    "SELECT TAP_UPLOAD.pos.cntr as in_row_id FROM wise.wise_allwise_p3am_cdd, TAP_UPLOAD.pos WHERE (ST_Intersects(TAP_UPLOAD.pos.poly,wise.wise_allwise_p3am_cdd.poly)) ORDER BY in_row_id ASC, dist_to_bounds ASC",
    "select CASEFULL from b",
    "select CASE foo WHEN a THEN 'c' END from b",
    "select CASE a WHEN 'b' THEN 'c' ELSE 'd' END from b",
    "select CASE a WHEN 'b' THEN 'c' ELSE NULL END from b",
    "select CASE a WHEN 'b' THEN 'c' when 'd' then 'e' ELSE 'f' END from b",
    "select cast('Inf' as FLOAT8), cast('-Inf' as Float4) from foo",
  };


  std::vector<std::string> fail = {
    "POINT('foo',10 20)", "POINT('foo',1.0, 20)", "POINT('foo',10 ,-2.0)",
    "SELECTTOP 100 * FROM my_table1",
    "SELECT TOP100 * FROM my_table1",
    "SELECT TOP 100* FROM my_table1",
    "SELECT TOP hundred * FROM my_table1",
    "SELECT DISTINCT sin FROM my_table1",
    "SELECT TOP 100 FROM my_table1",
    "SELECT * FROM my_table1 where x in(10,20,30)",
    "SELECT * FROM my_table1 where x not in(10,20,30)",
    "SELECT FROM my_table1 WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , "
    "20,1))",
    "SELECT * FROM WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , "
    "20,1))",
    "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
    "And x<1 And x>2 Or y < 3 Or y >5"
    "SELECT *,ra FROM my_table1",
    "SELECT my_tablel1.* as ra_dec FROM my_table1",
    "select sum(a,b) from a",
    "select sum from a",
    "select sum( from a",
    "select abs(a,b) from a",
    "select sin from a",
    "select sin() from a",
    "select sin( from a",
    "select atan2 from a",
    "select atan2() from a",
    "select atan2(a) from a",
    "select atan2(a,) from a",
    "select atan2(a,b from a",
    "select round from a",
    "select round() from a",
    "select round(a,) from a",
    "select round(a,b from a",
    "select round(a,10 from a",
    "select count(* from a",
    "select b from a where x<1 groupby a",
    "select b from a where x<1 group bya",
    "select b from a where x<1 orderby a",
    "select b from a where x<1 order bya",
    "select b from a where x<1 havinga",
    "select a asb from a group by a",
    "Select fromage ast from fromming",
    "SELECT * FROM my_table1 where (x notBetween 2 AND 4)",
    "SELECT * FROM my_table1 where x notin (10,20,30)",
    "SELECT * FROM mytable WHERECONTAINS(POINT('J2000',mytable.ra,dec),"
    "CIRCLE('J2000',+10 , -20,-1)) = 1",
    "SELECT * FROM mytable as my WHERECONTAINS(POINT('J2000',mytable.ra,dec),"
    "CIRCLE('J2000',+10 , -20,-1)) = 1",
    "SELECT * from TAP_UPLOAD.wrong_table",
    "SELECT TAP_UPLOAD.* from TAP_UPLOAD.mytable",
    "SELECT TAP_UPLOAD.wrong_table from TAP_UPLOAD.mytable",
    "SELECT TAP_UPLOAD.wrong_table.* from TAP_UPLOAD.mytable",
    "SELECT TAP_UPLOAD.wrong_table.ra from TAP_UPLOAD.mytable",
    "select CASE foo WHENever THEN 'c' END from b",
    "select alligator from (table1)",
  };

  int result(0);
  std::map<std::string,std::string>
    table_mapping={{"mytable","xyzzy"}, {"pos","T18cbfcb3b9100bef4036ed"}};
  for (auto &i : pass)
    {
      try
        {
          ADQL::Query query (i, table_mapping);
          std::string formatted_query=ADQL::to_string (query);
          ADQL::Query parsed_query(formatted_query);
          if(formatted_query!=ADQL::to_string (parsed_query))
            throw std::runtime_error("Reformatting formatted query gave different result:\n"
                                     "  Original:    " + i + "\n"
                                     + "  Formatted:   " + formatted_query + "\n"
                                     + "  Reformatted: " + ADQL::to_string (parsed_query));

          if(query.query_specification.top!=std::numeric_limits<unsigned long long>::max()
             && query.query_specification.top!=14223)
            throw std::runtime_error("Wrong value for TOP: "
                                     + std::to_string(query.query_specification.top));
          if(!quiet)
            {
              std::cout << "PASS: " << i << "\n";
              std::cout << "      " << formatted_query << "\n";
            }
        }
      catch (std::runtime_error &e)
        {
          std::cout << "FAIL: " << i << "\n";
          std::cout << "      " << e.what() << "\n";
          result=1;
        }
    }


  for (auto &i : fail)
    {
      try
        {
          ADQL::Query query (i,table_mapping);
          std::string formatted_query=ADQL::to_string (query);
          ADQL::Query parsed_query(formatted_query);

          if(formatted_query!=ADQL::to_string (parsed_query))
            throw std::runtime_error("");
          std::cout << "FAIL: Unexpected parse: " << i << "\n";
          result=1;
        }
      catch (std::runtime_error &e)
        {
          std::cout << "Query: " << i << "\n";
          std::cout << "error: " << e.what() << "\n";
          if(!quiet)
            std::cout << "PASS: " << i << "\n";
        }
    }

  return result;
}
