#include "../../ADQL_parser.hxx"

void ADQL_parser::init_geometry ()
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

  arithmetic_operator %= char_ ('+') | char_ ('-') | char_ ('*') | char_ ('/');
  arithmetic_operator.name ("arithmetic operator");

  binary_arithmetic_expression %= boost::spirit::qi::double_ >> arithmetic_operator >> boost::spirit::qi::double_;
  binary_arithmetic_expression.name ("binary arithmetic expression");

  column_or_simple_arithmetic_expression %= hold[binary_arithmetic_expression] | column_reference | boost::spirit::qi::double_;
  column_or_simple_arithmetic_expression.name ("column or simple arithmetic expression");

  coord %= column_or_simple_arithmetic_expression >> ',' > column_or_simple_arithmetic_expression;
  coord.name ("coordinate");

  // FIXME: In theory, the radius should be an expression.  In
  // practice, we can only handle column references, numbers, and
  // results of binary arithmetic operations.

  circle %= ascii::no_case["CIRCLE"] >> '(' >> -(coord_sys > ',') > coord > ','
            > column_or_simple_arithmetic_expression > ')';
  circle.name ("circle");

  ellipse %= ascii::no_case["ELLIPSE"] >> '(' >> -(coord_sys > ',') > coord
             > ',' > column_or_simple_arithmetic_expression > ',' > column_or_simple_arithmetic_expression > ','
             > column_or_simple_arithmetic_expression > ')';
  ellipse.name ("ellipse");

  box %= ascii::no_case["BOX"] >> '(' >> -(coord_sys > ',') > coord > ','
         > column_or_simple_arithmetic_expression > ',' > column_or_simple_arithmetic_expression > ')';
  box.name ("box");

  coord_list %= coord % ',';
  coord_list.name ("coordinate list");

  polygon %= ascii::no_case["POLYGON"] >> '(' >> -(coord_sys > ',')
             > coord_list > ')';
  polygon.name ("polygon");

  shape %= point | circle | box | ellipse | polygon;
  shape.name ("shape");

  contains %= ascii::no_case["CONTAINS"] >> '(' > point_or_column > ',' > shape
              > ')';
  contains.name ("contains");

  intersects %= ascii::no_case["INTERSECTS"] >> '(' > value_expression > ','
                > shape > ')';
  intersects.name ("intersects");

  geometry %= ((contains | intersects) >> -(lit ('=') >> '1'))
              | (lit ('1') >> '=' >> (contains | intersects));
  geometry.name ("geometry");
}
