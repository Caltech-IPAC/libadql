#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include "../src/Query.hxx"

// #define INVESTIGATE

// Warning: Tests will fail if "TOP" is specified with any value other than "14223".

int main(int argc, char *argv[]) {
    bool quiet(argc > 1 && argv[1] == std::string("-q"));
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
            "CONTAINS(POINT('J2000 Geocenter',ra,dec),CIRCLE('J2000 Geocenter',+10 , "
            "-20,-1))= 1",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "CONTAINS(POINT('J2000 Geocenter',ra,dec),BOX('J2000',+10 , -20,1,2))= 1",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "CONTAINS(POINT('J2000 Geocenter',ra,dec),ELLIPSE('J2000',+10 , "
            "-20,1,2,3))= 1",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "CONTAINS(POINT('J2000 Geocenter',ra,dec),ELLIPSE(+10 , -20,1,2,3))",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "CONTAINS(POINT('J2000 "
            "Geocenter',ra,dec),POLYGON('J2000',0,1,2,3,4,5,6,7,8,9,10,11,12,13))= 1",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "CONTAINS(POINT('J2000 "
            "Geocenter',ra,dec),POLYGON(0,1,2,3,4,5,6,7,8,9,10,11,12,13))",
            "SELECT * FROM mytable WHERE "
            "CONTAINS(POINT('J2000',mytable.ra,dec),CIRCLE('J2000',+10 , -20,-1)) = 1",
            "SELECT * FROM my_table WHERE "
            "1=CONTAINS(POINT('J2000',ra,my_table.dec),CIRCLE('J2000',+10 , -20,-1))",
            "SELECT * FROM my_table1 WHERE "
            "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , "
            "-20,-1))",
            "SELECT * FROM my_table1 WHERE "
            "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , "
            "-20,-1)) "
            "And (x<1)",
            "SELECT * FROM my_table1 WHERE (x!=3) and "
            "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , "
            "-20,-1))",
            "SELECT * FROM my_table1 WHERE x!=3",
            "SELECT * FROM my_table1",
            "SELECT * FROM my_table1 where x>2",
            "SELECT * FROM my_table1 where x>2 AND x<4",
            "SELECT * FROM my_table1 WHERE "
            "1= CONTAINS(POINT(my_table1.ra,dec),CIRCLE('J2000',+10 , -20,-1)) "
            "And (x<1 And x>2 Or y < 3 Or y >5)",
            "SELECT * FROM my_table1 WHERE "
            "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , "
            "-20,-1)) "
            "And (x<1 And x>2)",
            "SELECT * FROM my_table1 where (x AND x)",
            "SELECT * FROM my_table1 where (x>2 AND x<4) Or (x>6 and x<10)",
            "SELECT * FROM my_table1 where (x Between 2 AND 4) Or (x>6 and x<10)",
            "SELECT * FROM my_table1 where x is null",
            "SELECT * FROM my_table1 where x is not null",
            "SELECT * FROM fp_psc WHERE CONTAINS(POINT('J2000',ccc.fp_psc.ra, "
            "aaa.ccc.fp_pscdec),"
            "CIRCLE(1,1,0.08))=1 and (ra between 0.95 and 1.05)",
            "SELECT * FROM my_table1 where x in (select y from my_table2)",
            "SELECT * FROM my_table1 where x between y and z",
            "SELECT * FROM my_table1 where x or z",
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
            "SELECT abs(ra),ceiling(ra), "
            "degrees(ra),exp(ra),floor(ra),log(ra),log10(ra),"
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
            "select f(a, b, c), max(d), max(e) from t group by f(a,b,c)",
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

            // IRSA-2005
            "SELECT * FROM TAP_UPLOAD.mytable WHERE "
            "1= CONTAINS(POINT('J2000',TAP_UPLOAD.mytable.ra,TAP_UPLOAD.mytable.dec),"
            "CIRCLE('J2000',+10 , -20,-1)) ORDER BY TAP_UPLOAD.mytable.ra",
            "SELECT TAP_UPLOAD.mytable.ra as myra FROM TAP_UPLOAD.mytable WHERE "
            "1= CONTAINS(POINT('J2000',TAP_UPLOAD.mytable.ra,TAP_UPLOAD.mytable.dec),"
            "CIRCLE('J2000',+10 , -20,-1)) ORDER BY myra",

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
            "select alligator from table1 t1 join table2 t2 on a=b join table3 t3 on "
            "c=d join table4 t4 on e=f join table5 t5 on g=h",
            "select alligator from (table1 t1 join table2 t2 on a=b) join table3 t3 "
            "on c=d",
            "select alligator from table1 join table2 using (a,b, c )",
            "select TOP 14223 "
            "caom.observation.*,caom.plane.*,caom.artifact.*,caom.part.*,caom.chunk.* "
            "FROM caom.observation join caom.plane on caom.observation.obsid = "
            "caom.plane.obsid join caom.artifact on caom.plane.planeid = "
            "caom.artifact.planeid join caom.part on caom.artifact.artifactid = "
            "caom.part.artifactid join caom.chunk on caom.part.partid = "
            "caom.chunk.partid",
            "select TOP 14223 "
            "caom.observation.*,caom.plane.*,caom.artifact.*,caom.part.*,caom.chunk.* "
            "FROM (((caom.observation join caom.plane on caom.observation.obsid = "
            "caom.plane.obsid) join caom.artifact on caom.plane.planeid = "
            "caom.artifact.planeid) join caom.part on caom.artifact.artifactid = "
            "caom.part.artifactid) join caom.chunk on caom.part.partid = "
            "caom.chunk.partid",
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
            "select TAP_UPLOAD.mytable.x - TAP_UPLOAD.mytable.y as dx from "
            "TAP_UPLOAD.mytable, "
            "fp_psc",
            "select (fp_psc.x - fp_psc.y) + (TAP_UPLOAD.mytable.x - fp_psc.x) as dxy "
            "from fp_psc",
            "select fp_psc.x - TAP_UPLOAD.mytable.x from fp_psc, TAP_UPLOAD.mytable",
            "select TAP_UPLOAD.mytable.x - fp_psc.x from fp_psc, TAP_UPLOAD.mytable",
            "select * from herschel.observations where "
            "ST_Covers(poly,ST_Point(10,10))='t' "
            "or ST_Distance(poly,ST_Point(10,10)) <= 0.0",
            "select herschel.observations.*, "
            "ST_Distance(ST_Centroid(poly),ST_Point(84.912154,-69.652608)) "
            "as dist_to_centroid"
            " from herschel.observations where ST_Covers(poly,ST_Point(10,10))='t' "
            "or ST_Distance(poly,ST_Point(10,10)) <= 0.0",
            "select * from a where (1=0) AND (2=1) ORDER BY cntr ASC",
            "select '{a,b}' from c",
            "select ARRAY[10,20] from c",
            "select ARRAYNOT from c",
            "select a[b] from c",
            "select ((ARRAY[10,20])[1]) from c",
            "select ARRAY[10,20][1], "
            "(ARRAY[10,20])[1],(ARRAY[10,20])["
            "band][pass][info][5] from c",
            "select right(band), left(band,2) from c",
            "select ARRAY[10,20][band] * 1.0e-6 from c",
            "select upper(band), lower(band), trim(band) from c",
            "select mod(cast(foo as numeric),360.0) from c",
            "select * from twomass.full_images where "
            "(ST_DWithin(twomass.full_images.poly,ST_Point(1, "
            "1),0*111194.68229846345,'f'))",
            "SELECT schema_name as schemas FROM (select schema_name, min(table_index) "
            "as schema_index from TAP_SCHEMA.tables group by schema_name order by "
            "schema_index) as temp_schemas group by schemas order by schema_index",
            "select schema_name from (select schema_name, min(table_index) as "
            "schema_index from TAP_SCHEMA.tables group by schema_name order by "
            "schema_index) temp_schemas",
            "SELECT TAP_UPLOAD.pos.cntr as in_row_id FROM wise.wise_allwise_p3am_cdd, "
            "TAP_UPLOAD.pos WHERE "
            "(ST_Intersects(TAP_UPLOAD.pos.poly,wise.wise_allwise_p3am_cdd.poly)) "
            "ORDER BY in_row_id ASC, dist_to_bounds ASC",
            "select CASEFULL from b",
            "select CASE foo WHEN a THEN 'c' END from b",
            "select CASE a WHEN 'b' THEN 'c' ELSE 'd' END from b",
            "select CASE a WHEN 'b' THEN 'c' ELSE NULL END from b",
            "select CASE a WHEN 'b' THEN 'c' when 'd' then 'e' ELSE 'f' END from b",
            "select cast('Inf' as FLOAT8), cast('-Inf' as Float4) from foo",
            "select ST_MakeLine(ARRAY[ST_MakePoint(T5ad885ee5df7f9ca98e978.ra1, 2), "
            "ST_MakePoint(3, 4), ST_MakePoint(5, 6), ST_MakePoint(7, 8), "
            "ST_MakePoint(1, 2)]) from T5ad885ee5df7f9ca98e978",
            "select bar from foo where ('10' = ANY(bar))",
            "select NULLIf (a,b), Coalesce (a), Coalesce (a,b,c), Coalesce (a,b) from "
            "foo",
            "select CASe when b=1 then c when b=2 then e else f end from foo",
            "select CASe when b=1 then c when b=2 then e end from foo",
            "select Case when true then c else d end from foo",
            "select (CASE a WHEN b THEN c END) as d from foo",
            "SELECT o.target_name as name,"
            "          (p.time_bounds_lower + p.time_bounds_upper)/2 as "
            "DATE_TIME_OF_OBS,"
            "          o.proposal_id as PROGRAM_ID,"
            "          (CASE WHEN o.intent = 'science' THEN 'S'"
            "          WHEN o.target_standard  then 'T'"
            "                ELSE 'C' END)"
            "          as DY,"
            "          (o.instrument_name || ',' || o.instrument_keywords) as "
            "Instrument_Setup,"
            "          o.observationid as Group_ID,"
            "          MAX(CASE WHEN (a.productType='preview' and a.uri like "
            "'%_target.png') THEN"
            "            ('<a href=\"' || a.uri || '\">[T]<\a>') ELSE NULL END) as "
            "Target,"
            "          MAX(CASE WHEN (a.productType='info' and a.uri like "
            "'%program_%.txt') THEN"
            "            ('<a href=\"' || a.uri || '\">[P]<\a>') ELSE NULL END) as "
            "Program,"
            "          MAX(CASE WHEN (a.productType='preview' and a.uri like "
            "'%weather_%.png') THEN"
            "            ('<a href=\"' || a.uri || '\">[W]<\a>') ELSE NULL END) as "
            "Weather,"
            "          MAX(CASE WHEN (a.productType='preview' and a.uri like "
            "'%_qa.png') THEN"
            "            ('<a href=\"' || a.uri || '\">[Q]<\a>') ELSE NULL END) as "
            "Quality"
            "   FROM"
            "     (caom.plane p join caom.observation o on o.obsid = p.obsid) "
            "     join caom.artifact a on p.planeid = a.planeid "
            "   WHERE"
            "     INTERSECTS(caom.plane.poly, CIRCLE(10,10,1))"
            "     AND (caom.observation.telescope_name = 'IRTF'"
            "          AND (58036 <= caom.plane.time_bounds_upper"
            "               AND 58036 >= caom.plane.time_bounds_lower)"
            "          AND caom.observation.instrument = 'Spex Spectrograph')"
            "   GROUP BY"
            "     name, DATE_TIME_OF_OBS, PROGRAM_ID, DY, Instrument_Setup, Group_ID",
            "SELECT bar FROM foo where (ST(ST(ST(ST(ST(ST(ST(ST(ST())))))))))",
            "SELECT TAP_UPLOAD.pos.cntr as in_row_id, TAP_UPLOAD.pos.ra as in_ra, "
            "TAP_UPLOAD.pos.dec as in_dec, "
            "wise.wise_allwise_p3am_cdd.* "
            "FROM wise.wise_allwise_p3am_cdd, TAP_UPLOAD.pos "
            "WHERE (ST_Covers(ST_MakePolygon(ST_MakeLine(ARRAY["
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),"
            "111194.68229846345*0.5,radians(-90.0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),"
            "111194.68229846345*0.5,radians(-90.0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),"
            "111194.68229846345*0.5,radians(90.0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),"
            "111194.68229846345*0.5,radians(90.0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),"
            "111194.68229846345*0.5,radians(-90.0))])),"
            "ST_Point(wise.wise_allwise_p3am_cdd.ra1,wise.wise_allwise_p3am_cdd.dec1)) "
            "AND ST_Covers(ST_MakePolygon(ST_MakeLine(ARRAY["
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(-90.0)"
            "),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),111194.68229846345*0.5,radians(-"
            "90.0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(90.0))"
            ","
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),111194.68229846345*0.5,radians(90."
            "0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(-90.0)"
            ")])),ST_Point(wise.wise_allwise_p3am_cdd.ra2,wise.wise_allwise_p3am_cdd."
            "dec2)) "
            "AND ST_Covers(ST_MakePolygon(ST_MakeLine(ARRAY["
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(-90.0)"
            "),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),111194.68229846345*0.5,radians(-"
            "90.0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(90.0))"
            ","
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),111194.68229846345*0.5,radians(90."
            "0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(-90.0)"
            ")])),ST_Point(wise.wise_allwise_p3am_cdd.ra3,wise.wise_allwise_p3am_cdd."
            "dec3)) "
            "AND ST_Covers(ST_MakePolygon(ST_MakeLine(ARRAY["
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(-90.0)"
            "),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),111194.68229846345*0.5,radians(-"
            "90.0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(90.0))"
            ","
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(-180.0)),111194.68229846345*0.5,radians(90."
            "0)),"
            "ST_Project(ST_Project(ST_Point(TAP_UPLOAD.pos.ra,TAP_UPLOAD.pos.dec), "
            "111194.68229846345*0.5,radians(0.0)),111194.68229846345*0.5,radians(-90.0)"
            ")])),ST_Point(wise.wise_allwise_p3am_cdd.ra4,wise.wise_allwise_p3am_cdd."
            "dec4))"
            ") "
            "ORDER BY in_row_id ASC",
            "select * from mytable where a not like b",
            "Select * From mytable Where "
            "INTERSECTs(coalesce(pt,poly),Circle('J2000',+10 , -20,-1))",

            // IRSA-2131
            "SELECT distinct o.instrument_name, coord1(p.pt) AS ra FROM "
            "caom.observation_sofia o, caom.plane_sofia p WHERE o.obsid = p.obsid",
            "SELECT distinct o.instrument_name, coord2(p.pt) AS two FROM "
            "caom.observation_sofia o, caom.plane_sofia p WHERE o.obsid = p.obsid",

            // IRSA-4175
            "SELECT fp_psc.* from fp_psc, TAP_UPLOAD.mytable where "
            "1=CONTAINS(POINT('J2000',fp_psc.ra, fp.psc.dec), "
            "CIRCLE('J2000',TAP_UPLOAD.mytable.ra, TAP_UPLOAD.mytable.dec,"
            "12.8/2.34))",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "CONTAINS(POINT('J2000 Geocenter',ra,dec),ELLIPSE(+10 , -20,1,2,3 * 4.5))",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "CONTAINS(POINT('J2000 Geocenter',ra,dec),BOX('J2000',+10 , "
            "-20,1,2+3.33))= 1",

            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "1=CONTAINS(POINT('J2000',fp_psc.ra, fp.psc.dec), "
            "CIRCLE('J2000', 0.12 + 34.1, 4.545 - 2.9,"
            "12.8/2.34))",
            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "1=CONTAINS(POINT('J2000',fp_psc.ra, fp.psc.dec), "
            "CIRCLE('J2000', 0.12 + 34.1, 4.545 - 2.9,"
            "12.8/0))",
            "SELECT TOP 14223 b.unwise_objid as unwise_id, "
            "DISTANCE(POINT('ICRS', b.ra, b.dec), POINT('ICRS', mytable.ra, "
            "mytable.dec)) as unwise_dist "
            "from unwise_2019 b, TAP_UPLOAD.mytable mytable",

            "SELECT TAP_UPLOAD.pos.cntr as in_row_id, "
            "DISTANCE(POINT('ICRS', dbtable.ra, dbtable.dec), POINT('ICRS', "
            "mytable.ra, mytable.dec)) as unwise_dist "
            "FROM wise.wise_allwise_p3am_cdd dbtable, "
            "TAP_UPLOAD.pos WHERE "
            "(ST_Intersects(TAP_UPLOAD.pos.poly,dbtable.poly)) ",

            "SELECT props.proposal_id FROM (SELECT DISTINCT proposal_id FROM "
            "sofia.observation) middle, sofia.proposals props WHERE middle.proposal_id "
            "= props.proposal_id",

            // IRSA-4528
            "select NULL as null_col from foo",
            "select NULL::char as null_col from foo",
            "select ra,NULL::char as null_col from foo",
            "select ra,NULL::char,dec as null_col from foo",
            "select NULL::char from foo",
            "select NULL::int as null_col from foo",
            "select NULL::float as null_col from foo",

            // limited support for CAST
            "SELECT to_date(the_date,'J') AS real_date FROM fp_psc",
            "SELECT TOP 14223 jdate, to_char(to_date(floor(jdate), 'J')) AS real_date "
            "FROM fp_psc",
            "SELECT time_bounds_lower, cast(time_bounds_lower AS varchar) AS "
            "cast_lower FROM caom.plane",
            "SELECT time_bounds_lower, cast(time_bounds_lower AS text) AS cast_lower "
            "FROM caom.plane",
            "SELECT time_bounds_lower, cast(time_bounds_lower AS char) AS cast_lower "
            "FROM caom.plane",
            "SELECT time_bounds_lower, cast(time_bounds_lower AS varchar2) AS "
            "cast_lower FROM caom.plane",
            "SELECT  time_bounds_lower as mjd, time_bounds_lower+2400000.5 AS "
            "julian_date, "
            "to_date(cast(time_bounds_lower + 2400000.5 AS varchar),'J') AS real_date "
            "FROM caom.plane",
            "select cast('1' as bigint) AS my_col FROM caom.observation",

            // support for WITH
            "WITH tempTable (avgDist) (SELECT avg(dist) FROM distTable) "
            "SELECT table_name, dist FROM distTable, tempTable WHERE distTable.dist > "
            "tempTable.avgDist",

            "WITH alpha_subset (SELECT * FROM alpha_source WHERE mod(id,10) = 0) "
            "SELECT ra, dec FROM alpha_subset WHERE ra > 10 and ra < 20",

            "WITH tempTable (avgDist) AS (SELECT avg(dist) FROM distTable) "
            "SELECT table_name, dist FROM distTable, tempTable WHERE distTable.dist > "
            "tempTable.avgDist",

            "WITH alpha_subset AS (SELECT * FROM alpha_source WHERE mod(id,10) = 0) "
            "SELECT ra, dec FROM alpha_subset WHERE ra > 10 and ra < 20",

            // support for table() function
            "WITH temp (collection, multi_type) AS (SELECT collection,mytype "
            "FROM table(tap_ancillary.DCE_DATATYPE('irsa_directory'))) "
            "SELECT DISTINCT projectshort AS facility_name,description,"
            "irsa_directory.collection AS obs_collection FROM irsa_directory,temp "
            "WHERE irsa_directory.collection=temp.collection",

            "SELECT DISTINCT projectshort AS "
            "facility_name,description,irsa_directory.collection AS obs_collection,"
            "instrument AS instrument_name,coverage,band,info_url,temp.multi_type AS "
            "dataproduct_type "
            "FROM irsa_directory, (SELECT collection,mytype as multi_type "
            "FROM table(tap_ancillary.DCE_DATATYPE('irsa_directory'))) as temp "
            "WHERE semantics like '%primary%' AND "
            "irsa_directory.collection=temp.collection "
            "ORDER BY facility_name,irsa_directory.collection,instrument_name",

            // IRSA-5856

            "Select * From mytable JOIN dbtable WHERE "
            "INTERSECTs(mytable.mycol1,dbtable.col2)",

            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "1=CONTAINS(POINT('J2000',fp_psc.ra, fp.psc.dec), "
            "s_region)",

            "SELECT ra1 As rara, dec2, flux FROM mytable WHERE "
            "1=CONTAINS(POINT(fp_psc.ra, fp.psc.dec), "
            "poly)",

            "SELECT dataproduct_type,obs_id,obs_collection FROM ivoa.obscore WHERE "
            "CONTAINS(POINT(148.8882208, 69.06529472), s_region)=1 ORDER BY "
            "dataproduct_type,obs_id,obs_collection",

            // IRSA-5880
            "select string_agg(fname, ',') from spitzer.deepdrill_images",
            "select string_agg(distinct(instrument_name), ',') from ivoa.obscore",
    };

    std::vector<std::string> fail = {
            "POINT('foo',10 20)", "POINT('foo',1.0, 20)", "POINT('foo',10 ,-2.0)",
            "SELECTTOP 100 * FROM my_table1", "SELECT TOP100 * FROM my_table1",
            "SELECT TOP 100* FROM my_table1", "SELECT TOP hundred * FROM my_table1",
            "SELECT DISTINCT sin FROM my_table1", "SELECT TOP 100 FROM my_table1",
            "SELECT * FROM my_table1 where x in(10,20,30)",
            "SELECT * FROM my_table1 where x not in(10,20,30)",
            "SELECT FROM my_table1 WHERE CONTAINS(POINT('J2000',10 , "
            "20),CIRCLE('J2000',10 , "
            "20,1))",
            "SELECT * FROM WHERE CONTAINS(POINT('J2000',10 , 20),CIRCLE('J2000',10 , "
            "20,1))",
            "1= CONTAINS(POINT('J2000',my_table1.ra,dec),CIRCLE('J2000',+10 , "
            "-20,-1)) "
            "And x<1 And x>2 Or y < 3 Or y >5"
            "SELECT *,ra FROM my_table1",
            "SELECT my_tablel1.* as ra_dec FROM my_table1", "select sum(a,b) from a",
            "select sum from a", "select sum( from a", "select abs(a,b) from a",
            "select sin from a", "select sin() from a", "select sin( from a",
            "select atan2 from a", "select atan2() from a", "select atan2(a) from a",
            "select atan2(a,) from a", "select atan2(a,b from a", "select round from a",
            "select round() from a", "select round(a,) from a",
            "select round(a,b from a", "select round(a,10 from a",
            "select count(* from a", "select b from a where x<1 groupby a",
            "select b from a where x<1 group bya",
            "select b from a where x<1 orderby a",
            "select b from a where x<1 order bya", "select b from a where x<1 havinga",
            "select a asb from a group by a", "Select fromage ast from fromming",
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

            // IRSA-2005
            "SELECT column_name,description,unit,ucd,utype,datatype,principal,indexed "
            "from TAP_SCHEMA.columns where table_name='ztf.ztf_current_meta_sci' "
            "order by column_index'A=0"

    };

    int result(0);

    std::map<std::string, std::string> table_mapping = {
            {"mytable", "xyzzy"}, {"pos", "T18cbfcb3b9100bef4036ed"}};
    for (auto &i : pass) {
#ifdef INVESTIGATE
        std::cout << "testing, top of pass loop, i: " << i << std::endl << std::flush;
#endif
        try {
            size_t initial_size(std::count(i.begin(), i.end(), '*'));

            ADQL::Query query(i, table_mapping);
#ifdef INVESTIGATE
            std::cout << "test, before to_string()" << std::endl;
#endif
            std::string formatted_query = ADQL::to_string(query);
#ifdef INVESTIGATE
            std::cout << "formatted_query: " << formatted_query << std::endl;
#endif
            size_t formatted_size(
                    std::count(formatted_query.begin(), formatted_query.end(), '*'));
            ADQL::Query parsed_query(formatted_query);
            if (initial_size != formatted_size ||
                formatted_query != ADQL::to_string(parsed_query))
                throw std::runtime_error(
                        "Reformatting formatted query gave different result:\n"
                        "  Original:    " +
                        i + "\n" + "  Formatted:   " + formatted_query + "\n" +
                        "  Reformatted: " + ADQL::to_string(parsed_query));

            if (query.query_specification.top != std::numeric_limits<size_t>::max() &&
                query.query_specification.top != 14223)
                throw std::runtime_error("Wrong value for TOP: " +
                                         std::to_string(query.query_specification.top));

            std::cout << "PASS: " << i << "\n";
            if (!quiet) {
                std::cout << "      " << formatted_query << "\n";
            }
        } catch (std::runtime_error &e) {
            std::cout << "FAIL: " << i << "\n";
            std::cout << "      " << e.what() << "\n";
            result = 1;
        }
    }

    for (auto &i : fail) {
        try {
#ifdef INVESTIGATE
            std::cout << "testing, top of fail loop, i: " << i << std::endl
                      << std::flush;
#endif
            ADQL::Query query(i, table_mapping);
            std::string formatted_query = ADQL::to_string(query);
            ADQL::Query parsed_query(formatted_query);

            if (formatted_query != ADQL::to_string(parsed_query))
                throw std::runtime_error("");
            std::cout << "FAIL: Unexpected parse: " << i << "\n";
            result = 1;
        } catch (std::runtime_error &e) {
            std::cout << "PASS (malformed query detected): " << i << "\n";
            if (!quiet) {
                std::cout << "Fail Query: " << i << "\n";
                std::cout << "error: " << e.what() << "\n";
            }
        }
    }

    return result;
}
