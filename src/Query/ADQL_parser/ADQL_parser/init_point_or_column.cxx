#include "../../ADQL_parser.hxx"

void ADQL_parser::init_point_or_column() {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::labels::_val;

    namespace ascii = boost::spirit::ascii;

    coord_sys %=
            '\'' >>
            -(ascii::no_case["J2000"]
                            [at_c<0>(_val) = ADQL::Coord_Sys::Reference_Frame::J2000] |
              ascii::no_case["GALACTIC"]
                            [at_c<0>(_val) =
                                     ADQL::Coord_Sys::Reference_Frame::Galactic] |
              ascii::no_case["ICRS"]
                            [at_c<0>(_val) = ADQL::Coord_Sys::Reference_Frame::ICRS]) >>
            -ascii::no_case["GEOCENTER"]
                           [at_c<1>(_val) =
                                    ADQL::Coord_Sys::Reference_Position::GEOCENTER] >>
            '\'';
    coord_sys.name("coordinate system");

    point %= ascii::no_case["POINT"] >> '(' >> -(coord_sys > ',') > coord > ')';
    point.name("point");

    point_or_column %= point | column_reference;
    point_or_column.name("point or column");
}
