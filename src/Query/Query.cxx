#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/io.hpp>

#include "../Query.hxx"

template <typename Iterator>
struct ADQL_parser : boost::spirit::qi::grammar<Iterator, ADQL::Coordinate(),
                                                boost::spirit::ascii::space_type>
{
  ADQL_parser() : ADQL_parser::base_type(start)
  {
    start %= boost::spirit::qi::double_ >> ',' >> boost::spirit::qi::double_;
  }

  boost::spirit::qi::rule<Iterator, ADQL::Coordinate(),
                          boost::spirit::ascii::space_type> start;
};


ADQL::Query::Query(const std::string &input)
{
  ADQL_parser<std::string::const_iterator> p;
  Coordinate coord;
  std::string::const_iterator begin(input.begin()), end(input.end());

  bool valid(phrase_parse(begin,end,p,boost::spirit::ascii::space,coord));

  if(valid && begin==end)
    {
      std::cout << "Valid "
                << coord.ra << " "
                << coord.dec << " "
                << "\n";
    }
  else
    {
      std::cout << "Invalid\n";
    }
}
