#include "../../ADQL_parser.hxx"

void ADQL_parser::init_geometry()
{
  using boost::phoenix::at_c;
  using boost::phoenix::push_back;
  using boost::spirit::qi::labels::_val;
  using boost::spirit::qi::labels::_1;
  using boost::spirit::qi::labels::_2;
  using boost::spirit::qi::labels::_3;
  using boost::spirit::qi::lit;
  using boost::spirit::qi::char_;
  using boost::spirit::qi::alpha;
  using boost::spirit::qi::alnum;
  using boost::spirit::qi::digit;
  using boost::spirit::qi::double_;
  using boost::spirit::qi::ulong_long;
  using boost::spirit::qi::hold;
  using boost::spirit::qi::lower;
  using boost::spirit::qi::omit;
  using boost::spirit::qi::print;
  using boost::spirit::qi::lexeme;
  using boost::spirit::qi::no_skip;
  namespace ascii = boost::spirit::ascii;

  coord_sys
    %= '\''
    >> -(ascii::no_case["J2000"]
         [at_c<0>(_val)
          = ADQL::Coord_Sys::Reference_Frame::J2000]
         | ascii::no_case["GALACTIC"]
         [at_c<0>(_val)
          = ADQL::Coord_Sys::Reference_Frame::Galactic]
         | ascii::no_case["ICRS"]
         [at_c<0>(_val)
          = ADQL::Coord_Sys::Reference_Frame::ICRS])
    >> -ascii::no_case["GEOCENTER"]
    [at_c<1>(_val)
     = ADQL::Coord_Sys::Reference_Position::GEOCENTER]
    >> '\'';
  coord_sys.name ("coordinate system");
  
  column_or_number %= column_reference | boost::spirit::qi::double_;
  column_or_number.name ("column or number");
  coord %= column_or_number >> ',' > column_or_number;
  coord.name ("coordinate");
  point %= ascii::no_case["POINT"] >> '(' >> coord_sys > ',' > coord
                                   > ')';
  point.name ("point");
  point_or_column %= point | column_reference;

  // FIXME: In theory, the radius should be an expression, not a
  // number.  In practice, we can only handle numbers.
  circle %= ascii::no_case["CIRCLE"] >> '(' >> coord_sys > ',' > coord
                                     > ',' > column_or_number > ')';
  circle.name ("circle");
  ellipse %= ascii::no_case["ELLIPSE"] >> '(' >> coord_sys > ',' > coord
                                       > ',' > column_or_number > ','
                                       > column_or_number > ','
                                       > column_or_number > ')';
  ellipse.name ("ellipse");
  box %= ascii::no_case["BOX"] >> '(' >> coord_sys > ',' > coord > ','
                               > column_or_number > ',' > column_or_number
                               > ')';
  box.name ("box");
  coord_list %= coord % ',';
  coord_list.name ("coordinate list");
  polygon %= ascii::no_case["POLYGON"] >> '(' >> coord_sys > ','
                                       > coord_list > ')';
  polygon.name ("polygon");
  
  shape %= circle | box | ellipse | polygon;
  shape.name ("shape");
  contains %= ascii::no_case["CONTAINS"] >> '(' > point_or_column > ',' > shape
                                         > ')';
  contains.name ("contains");
  intersects %= ascii::no_case["INTERSECTS"] >> '(' > column_reference > ','
                                             > shape > ')';
  intersects.name ("intersects");
  
  geometry %= (contains >> -(lit('=') >> '1')) | (lit ('1') >> '=' >> contains);
  geometry.name ("geometry");
}
