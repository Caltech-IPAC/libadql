#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/io.hpp>

#include "../Query.hxx"

template <typename Iterator>
struct ADQL_parser : boost::spirit::qi::grammar<Iterator, ADQL::Contains(),
                                                boost::spirit::ascii::space_type>
{
  ADQL_parser() : ADQL_parser::base_type(contains)
  {
    coord_sys %=
      '\'' >> -boost::spirit::qi::lit("J2000")
      [boost::phoenix::at_c<0>(boost::spirit::qi::labels::_val)=
       ADQL::Coord_Sys::Reference_Frame::J2000]
           >> -boost::spirit::qi::lit("GEOCENTER")
      [boost::phoenix::at_c<1>(boost::spirit::qi::labels::_val)=
       ADQL::Coord_Sys::Reference_Position::GEOCENTER]
           >> '\'';

    coord %= boost::spirit::qi::double_ >> ',' >> boost::spirit::qi::double_;
    point %= "POINT(" >> coord_sys >> "," >> coord >> ")";

    circle %= "CIRCLE(" >> coord_sys >> "," >> coord >> ','
                       >> boost::spirit::qi::double_ >> ")";

    contains %= "CONTAINS(" >> point >> "," >> circle >> ")";
  }

  boost::spirit::qi::rule<Iterator, ADQL::Coord_Sys(),
                          boost::spirit::ascii::space_type> coord_sys;
  boost::spirit::qi::rule<Iterator, ADQL::Coordinate(),
                          boost::spirit::ascii::space_type> coord;

  boost::spirit::qi::rule<Iterator, ADQL::Point(),
                          boost::spirit::ascii::space_type> point;
  boost::spirit::qi::rule<Iterator, ADQL::Circle(),
                          boost::spirit::ascii::space_type> circle;

  boost::spirit::qi::rule<Iterator, ADQL::Contains(),
                          boost::spirit::ascii::space_type> contains;
};


ADQL::Query::Query(const std::string &input)
{
  ADQL_parser<std::string::const_iterator> parser;
  Contains contains;
  std::string::const_iterator begin(input.begin()), end(input.end());

  bool valid(phrase_parse(begin,end,parser,
                          boost::spirit::ascii::space,contains));

  if(valid && begin==end)
    {
      std::cout << "Valid '" << input << "' "
                << contains.point.coordinate.ra << " "
                << contains.point.coordinate.dec << " "
                << "\n";
    }
  else
    {
      std::cout << "Invalid '" << input << "'\n";
    }
}
