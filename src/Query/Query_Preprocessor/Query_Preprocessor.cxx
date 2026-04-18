#include "../Query_Preprocessor.hxx"

#include <iostream>

#include "Query_Preprocessor_Utils.hxx"
#include "Top_Level_Parser.hxx"
#include "Where_Clause_Normalizer.hxx"

using namespace ADQL::Query_Preprocessor_Utils;

// In the language of the ADQL_parser, the main parser defined in this
// repo, a geometry is a constraint involving one of the keywords
// CONTAINS and INTERSECTS, and a search_condition is any other kind
// of supported constraint or combination thereof.  For example:

// geometry:  "INTERSECTS(s_region, CIRCLE('ICRS',162.1, -38.9, 0.002))=1"

// search_condition:  "mjd>=55550.0 AND mjd<=65650.5"

// The number and nesting-complexity of search_conditions within a
// WHERE clause are not explicitly limited, but at most one geometry
// is allowed per WHERE clause because of query_server limitations.

// The present implementation of the ADQL_parser requires that if a
// WHERE clause contains a geometry, that geometry must precede any
// other constraints in the WHERE clause. End-users find this
// requirement irksome, but modifying the boost::spirit code to lift
// this requirement without violating restrictions imposed by the
// query_server, libadql's primary client, would be difficult if not
// impossible.  Claude advises against the attempt.

// Instead, we call the preprocess() function below to intercept
// incoming queries and modify their WHERE clauses as needed using
// plain C++ before handing off to the ADQL_Parser and boost::spirit.

//=========================================================

namespace ADQL {

namespace Query_Preprocessor {
Top_Level_Components preprocess(const std::string &input) {
    Top_Level_Components components = parse_top_level(input);

    std::string::size_type contains_pos, intersects_pos;
    if (check_for_geometry_keywords(input, 0, contains_pos, intersects_pos)) {
        for (auto &[op, sfw_str] : components.union_op_and_sfw_pairs_) {
            sfw_str = Where_Clause_Normalizer(sfw_str).get_normalized_where_clause();
        }
    }
    return components;
}

//=======================================

}  // namespace Query_Preprocessor
}  // namespace ADQL
