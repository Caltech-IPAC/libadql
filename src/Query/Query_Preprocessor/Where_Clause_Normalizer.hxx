#pragma once

#include <string>

namespace ADQL {

//=============================================================
// Normalizes the WHERE clause of a single SELECT...FROM...WHERE
// string by ensuring that the geometric constraint (CONTAINS or
// INTERSECTS), if such exists, precedes any search conditions.
//
// For example:
//
//   SELECT ... FROM ... WHERE (x>1) AND CONTAINS(...)=1 AND y<2
//
// is normalized to:
//
//   SELECT ... FROM ... WHERE CONTAINS(...)=1 AND (x>1) AND y<2
//
// If the geometric constraint is already first, or there is no
// geometric constraint, the original SELECT...FROM...WHERE string is
// returned unchanged.
// =============================================================

class Where_Clause_Normalizer {
public:
    explicit Where_Clause_Normalizer(const std::string &component);

    // Returns the normalized component string. If no rewrite was
    // needed, returns the original component string.
    std::string get_normalized_where_clause() const;

private:
    std::string rewrite() const;

    const std::string &component_;
    bool needs_rewrite_ = false;

    std::string pre_where_;
    std::string left_search_condition_;
    std::string logical_op_;
    std::string geometry_;
    std::string post_geom_parens_;
    std::string right_search_condition_;
};

}  // namespace ADQL
