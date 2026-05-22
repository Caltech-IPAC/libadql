#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <vector>

// A general ADQL query supported by LibADQL can be split into 3 parts as follows:

// (1) An optional WITH clause

// (2) One or more SELECT...FROM... or
//     SELECT...FROM...WHERE... combinations joined by some flavor of
//     UNION

// (3) Optional HAVING, GROUP BY, and/or ORDER BY clauses.

// For example:

// "WITH tempTable (avgDist) AS (SELECT avg(dist) FROM distTable) "

// "SELECT table_name, dist FROM distTable, tempTable WHERE distTable.dist > "
// "tempTable.avgDist * 10 UNION "

// "SELECT table_name, dist FROM distTable, tempTable WHERE distTable.dist < "
// " tempTable.avgDist / 10 "

// " ORDER BY dist "

// In what follows, "SFW" represents a SELECT...FROM...[WHERE...] string.

// The components of the Top_Level_Components class correspond to
// these parts of a single decomposed ADQL query.  Each SFW
// combination except the first is paired with the UNION operator
// preceding it (UNION, UNION ALL, or UNION DISTINCT); the first SFW
// is paired with the empty string.

namespace ADQL {

struct Top_Level_Components {
    typedef std::vector<std::pair<std::string, std::string>> Union_Op_And_SFW_Pairs;
    std::string with_clause_;
    Union_Op_And_SFW_Pairs union_op_and_sfw_pairs_;
    std::string trailing_clauses_;
};

}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(
        ADQL::Top_Level_Components,
        (std::string, with_clause_)(ADQL::Top_Level_Components::Union_Op_And_SFW_Pairs,
                                    union_op_and_sfw_pairs_)(std::string,
                                                             trailing_clauses_))
