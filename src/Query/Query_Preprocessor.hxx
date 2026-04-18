#pragma once
#include "Query_Preprocessor/Top_Level_Components.hxx"

// This function takes as its argument an incoming query string and
// returns a Top_Level_Components structure based on that string whose
// select_from_where substrings have been modified to suit the
// ADQL_parser's requirements related to geometric constraints.

namespace ADQL {

namespace Query_Preprocessor {

Top_Level_Components preprocess(const std::string &input);

}
}  // namespace ADQL
