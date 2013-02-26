#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/io.hpp>

#include "../Query.hxx"

template <typename Iterator>
struct ADQL_parser : boost::spirit::qi::grammar<Iterator, ADQL::Query(),
                                                boost::spirit::ascii::space_type>
{
  ADQL_parser() : ADQL_parser::base_type(query)
  {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::labels::_val;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;

    simple_Latin_upper_case_letter%=char_("A-Z");
    simple_Latin_lower_case_letter%=char_("a-z");
    simple_Latin_letter%=simple_Latin_upper_case_letter
      | simple_Latin_lower_case_letter;

    // regular_identifier=*(digit | simple_Latin_letter | '_')
    regular_identifier= *(digit | char_("a-zA-Z") | '_');

    // regular_identifier=simple_Latin_letter [push_back(_val,_1)]
    //   >> *((digit | simple_Latin_letter | '_') [push_back(_val,_1)]);

    // identifier=regular_identifier;  // FIXME: add delimited identifier
    identifier%=+char_("a-z");  // FIXME: add delimited identifier

    coord_sys %=
      '\'' >> -lit("J2000")
      [at_c<0>(_val)=ADQL::Coord_Sys::Reference_Frame::J2000]
           >> -lit("GEOCENTER")
      [at_c<1>(_val)=ADQL::Coord_Sys::Reference_Position::GEOCENTER]
           >> '\'';

    coord %= boost::spirit::qi::double_ >> ',' >> boost::spirit::qi::double_;
    point %= "POINT(" >> coord_sys >> "," >> coord >> ")";

    circle %= "CIRCLE(" >> coord_sys >> "," >> coord >> ','
                       >> boost::spirit::qi::double_ >> ")";

    contains %= "CONTAINS(" >> point >> "," >> circle >> ")";

    geometry %= contains;

    query =
      lit("SELECT") >> ((identifier % ',') [at_c<0>(_val)=_1])
                    >> "FROM" >> (identifier [at_c<1>(_val)=_1])
                    >> "WHERE" >> (geometry [at_c<2>(_val)=_1]);
  }

  boost::spirit::qi::rule<Iterator, char(), boost::spirit::ascii::space_type>
  simple_Latin_upper_case_letter;
  boost::spirit::qi::rule<Iterator, char(), boost::spirit::ascii::space_type>
  simple_Latin_lower_case_letter;
  boost::spirit::qi::rule<Iterator, char(),
                          boost::spirit::ascii::space_type> simple_Latin_letter;

  boost::spirit::qi::rule<Iterator, std::string(),
                          boost::spirit::ascii::space_type> regular_identifier;
  boost::spirit::qi::rule<Iterator, std::string(),
                          boost::spirit::ascii::space_type> identifier;

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

  boost::spirit::qi::rule<Iterator, ADQL::Geometry(),
                          boost::spirit::ascii::space_type> geometry;

  boost::spirit::qi::rule<Iterator, ADQL::Query(),
                          boost::spirit::ascii::space_type> query;
};


ADQL::Query::Query(const std::string &input)
{
  ADQL_parser<std::string::const_iterator> parser;
  std::string::const_iterator begin(input.begin()), end(input.end());

  bool valid(phrase_parse(begin,end,parser,
                          boost::spirit::ascii::space,*this));

  if(valid && begin==end)
    {
      std::cout << "Valid '" << input << "'\n";
      for(auto &o: output_columns)
        std::cout << o << " ";
      std::cout << "\n"
                << table << " "
                << geometry.contains.point.coordinate.ra << " "
                << geometry.contains.point.coordinate.dec << " "
                << "\n";
    }
  else
    {
      std::string rest(begin,end);
      std::cout << "Invalid '" << input << "'\n"
                << "Parsing stopped at: '"
                <<  rest << "'\n";
    }
}
