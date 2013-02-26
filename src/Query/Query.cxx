#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/io.hpp>

#include "../Query.hxx"

template <typename Iterator>
struct ADQL_parser : boost::spirit::qi::grammar<Iterator, ADQL::Contains(),
                                                boost::spirit::ascii::space_type>
{
  ADQL_parser() : ADQL_parser::base_type(contains)
  {
    quoted_string %= boost::spirit::qi::lexeme['\'' >> +(boost::spirit::ascii::char_ - '\'') >> '\''];
 
    coord %= boost::spirit::qi::double_ >> ',' >> boost::spirit::qi::double_;
    point %= "POINT(" >> quoted_string >> "," >> coord >> ")";

    circle %= "CIRCLE(" >> quoted_string >> "," >> coord >> ','
                       >> boost::spirit::qi::double_ >> ")";

    contains %= "CONTAINS(" >> point >> "," >> circle >> ")";
  }

  boost::spirit::qi::rule<Iterator, std::string(),
                          boost::spirit::ascii::space_type> quoted_string;
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
