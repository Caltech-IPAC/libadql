#include "../../ADQL_parser.hxx"

void ADQL_parser::init_point_or_column() {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::labels::_val;

    namespace ascii = boost::spirit::ascii;

    reference_frames.add("icrs", ADQL::Coord_Sys::Reference_Frame::ICRS)(
            "j2000", ADQL::Coord_Sys::Reference_Frame::J2000)(
            "galactic", ADQL::Coord_Sys::Reference_Frame::Galactic);
    reference_frame %= ascii::no_case[reference_frames];
    reference_frame.name("reference frame");

    reference_positions.add("geocenter",
                            ADQL::Coord_Sys::Reference_Position::GEOCENTER);
    reference_position %= ascii::no_case[reference_positions];
    reference_position.name("reference position");

    coord_sys %=
            '\'' >> -(ascii::no_case[reference_frame]) >> -(reference_position) >> '\'';
    coord_sys.name("coordinate system");

    point %= ascii::no_case["POINT"] >> '(' >> -(coord_sys > ',') > coord > ')';
    point.name("point");

    point_or_column %= point | column_reference;
    point_or_column.name("point or column");

#ifdef DEBUG_WHERE
    BOOST_SPIRIT_DEBUG_NODE(reference_frame);
    BOOST_SPIRIT_DEBUG_NODE(reference_position);
    BOOST_SPIRIT_DEBUG_NODE(coord_sys);
    BOOST_SPIRIT_DEBUG_NODE(point);
    BOOST_SPIRIT_DEBUG_NODE(point_or_column);
#endif
}
