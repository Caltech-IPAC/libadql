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

  coord %= numeric_value_expression >> ',' >> numeric_value_expression;
  point %= ascii::no_case["POINT"] >> '(' >> coord_sys >> ',' >> coord
                                   >> ')';

  // FIXME: In theory, the radius should be an expression, not a
  // number.  In practice, we can only handle numbers.
  circle %= ascii::no_case["CIRCLE"] >> '(' >> coord_sys >> ',' >> coord
                                     >> ',' >> boost::spirit::qi::double_ >> ')';
  ellipse %= ascii::no_case["ELLIPSE"] >> '(' >> coord_sys >> ',' >> coord
                                       >> ',' >> boost::spirit::qi::double_ >> ','
                                       >> boost::spirit::qi::double_ >> ','
                                       >> boost::spirit::qi::double_ >> ')';
  box %= ascii::no_case["BOX"] >> '(' >> coord_sys >> ',' >> coord >> ','
                               >> boost::spirit::qi::double_ >> ',' >> boost::spirit::qi::double_
                               >> ')';
  coord_list %= coord % ',';
  polygon %= ascii::no_case["POLYGON"] >> '(' >> coord_sys >> ','
                                       >> coord_list >> ')';

  shape %= circle | box | ellipse | polygon;
  contains %= ascii::no_case["CONTAINS"] >> '(' >> point >> ',' >> shape
                                         >> ')';

  geometry %= (contains >> '=' >> '1') | (lit ('1') >> '=' >> contains);
}
