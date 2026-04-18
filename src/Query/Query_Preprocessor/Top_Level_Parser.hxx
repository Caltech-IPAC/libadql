#pragma once

#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>

#include "Top_Level_Components.hxx"

// This parser parses a general ADQL query into the 3 components
// described in Top_Level_Components.hxx, thus making the query's
// select_from_where strings accessible to the Query_Preprocessor.

namespace ADQL {

struct Top_Level_Parser
        : boost::spirit::qi::grammar<std::string::const_iterator,
                                     Top_Level_Components(),
                                     boost::spirit::qi::locals<std::string>> {
    Top_Level_Parser();

    boost::spirit::qi::rule<std::string::const_iterator> single_quoted, double_quoted,
            parenthesized, opaque_token;

    boost::spirit::qi::rule<std::string::const_iterator, std::string()> with_clause,
            select_from_where_component, union_op, trailing_clauses;

    boost::spirit::qi::rule<std::string::const_iterator, Top_Level_Components(),
                            boost::spirit::qi::locals<std::string>>
            query;
};

Top_Level_Components parse_top_level(const std::string &input);

}  // namespace ADQL
