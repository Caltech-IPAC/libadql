#include "../Where_Clause_Normalizer.hxx"

#include <optional>
#include <sstream>
#include <stdexcept>

#include "../Query_Preprocessor_Utils.hxx"

using namespace ADQL::Query_Preprocessor_Utils;

namespace {

static constexpr uint AND_LEN = 3;
static constexpr uint OR_LEN = 2;
static constexpr uint WHERE_LEN = 5;  // strlen("WHERE")

//=======================================================
// Returns the position of the right-most AND or OR between left and
// right, or npos if none found.

std::string::size_type find_last_logical_op(const std::string &input,
                                            std::string::size_type left,
                                            std::string::size_type right) {
    auto and_pos = case_insensitive_rfind(input, "AND", left, right);
    auto or_pos = case_insensitive_rfind(input, "OR", left, right);
    if (and_pos == std::string::npos) {
        return or_pos;
    }
    if (or_pos == std::string::npos) {
        return and_pos;
    }
    return std::max(and_pos, or_pos);
}

//=======================================================
// Scans forward from an '(', handling nested parentheses. Returns
// the position of the corresponding closing paren, or npos on failure.

std::string::size_type find_paren_partner_pos(const std::string &input,
                                              std::string::size_type start_pos) {
    if (start_pos >= input.size() || input[start_pos] != '(') {
        return start_pos;
    }
    int depth = 0;
    for (auto pos = start_pos; pos < input.size(); ++pos) {
        if (input[pos] == '(') {
            ++depth;
        } else if (input[pos] == ')') {
            if (--depth == 0) {
                return pos;
            }
        }
    }
    return std::string::npos;
}

//=======================================================

std::optional<std::string> get_logical_op_str(const std::string &input,
                                              std::string::size_type pos) {
    if (case_insensitive_find(input, "AND", pos) == pos) {
        return std::string("AND");
    }
    if (case_insensitive_find(input, "OR", pos) == pos) {
        return std::string("OR");
    }
    return std::nullopt;
}

}  // namespace

//=========================================================
//=========================================================

namespace ADQL {

Where_Clause_Normalizer::Where_Clause_Normalizer(const std::string &component)
        : component_(component) {
    // Find WHERE clause
    auto where_start_pos = case_insensitive_find(component_, "WHERE ");
    if (where_start_pos == std::string::npos) {
        return;  // no WHERE clause, no rewrite needed
    }
    auto post_where_pos = where_start_pos + WHERE_LEN + 1;

    // Find ADQL geometry keywords
    std::string::size_type contains_pos, intersects_pos;
    if (!check_for_geometry_keywords(component_, post_where_pos, contains_pos,
                                     intersects_pos)) {
        return;  // no geometry, no rewrite needed
    }

    auto geom_fcn_start_pos =
            (contains_pos != std::string::npos) ? contains_pos : intersects_pos;

    // Find the last logical op before the geometry
    auto left_op_pos =
            find_last_logical_op(component_, post_where_pos, geom_fcn_start_pos);
    if (left_op_pos == std::string::npos) {
        return;  // geometry already first, no rewrite needed
    }

    // Find the geometry function's argument parens
    auto open_paren_pos = component_.find('(', geom_fcn_start_pos);
    if (open_paren_pos == std::string::npos) {
        throw std::runtime_error("INTERSECTS/CONTAINS must be followed by '('.");
    }

    auto geom_fcn_end_pos = find_paren_partner_pos(component_, open_paren_pos);
    if (geom_fcn_end_pos == std::string::npos) {
        throw std::runtime_error("INTERSECTS/CONTAINS must be followed by '(...)'.");
    }

    // Determine logical op
    auto logical_op = get_logical_op_str(component_, left_op_pos);
    if (!logical_op) {
        throw std::runtime_error(
                "Failed to extract the logical operator preceding "
                "INTERSECTS/CONTAINS.");
    }

    // If we get here, there is a search_condition preceding the geometry.
    needs_rewrite_ = true;

    logical_op_ = *logical_op;
    uint active_op_len = (logical_op_ == "AND") ? AND_LEN : OR_LEN;
    const char *inactive_op_str = (logical_op_ == "AND") ? "OR" : "AND";

    // Extract pre_where (everything up to and including "WHERE ")
    pre_where_ = component_.substr(0, where_start_pos) + "WHERE ";

    // Extract left_search_condition (from post_where to just before left_op)
    auto left_start = component_.find_first_not_of(' ', post_where_pos);
    auto left_end = component_.find_last_not_of(' ', left_op_pos - 1);
    left_search_condition_ = component_.substr(left_start, left_end - left_start + 1);

    // Extract geometry including optional =0/=1 suffix
    auto geom_prefix_start =
            component_.find_first_not_of(' ', left_op_pos + active_op_len);
    auto geom_suffix_end = geom_fcn_end_pos;
    {
        auto pos = component_.find_first_not_of(' ', geom_fcn_end_pos + 1);
        if (pos != std::string::npos && component_[pos] == '=') {
            auto val_pos = component_.find_first_not_of(' ', pos + 1);
            if (val_pos != std::string::npos &&
                (component_[val_pos] == '0' || component_[val_pos] == '1')) {
                geom_suffix_end = val_pos;
            }
        }
    }
    geometry_ = component_.substr(geom_prefix_start,
                                  geom_suffix_end - geom_prefix_start + 1);

    // Extract post_geom_parens: the closing parens immediately after geometry
    auto post_geom_pos = geom_suffix_end;
    if (geom_suffix_end != component_.size()) {
        auto pos = component_.find_first_not_of(' ', geom_suffix_end + 1);
        while (pos != std::string::npos && component_[pos] == ')') {
            post_geom_parens_ += ')';
            pos = component_.find_first_not_of(' ', pos + 1);
        }
        if (!post_geom_parens_.empty()) {
            post_geom_pos = (pos != std::string::npos) ? pos : component_.size();
        }
    }

    // Extract right_search_condition:  everything after post_geom_parens and the active
    // op
    auto right_sc_end = component_.size();
    auto right_active_op_pos =
            case_insensitive_find(component_, logical_op_, post_geom_pos);
    auto right_inactive_op_pos =
            case_insensitive_find(component_, inactive_op_str, post_geom_pos);
    if (right_inactive_op_pos != std::string::npos &&
        (right_active_op_pos == std::string::npos ||
         right_inactive_op_pos < right_active_op_pos)) {
        throw std::runtime_error(
                "mixed AND/OR operators around geometric constraint are not supported");
    }
    if (right_active_op_pos != std::string::npos &&
        right_active_op_pos < right_sc_end) {
        auto right_start =
                component_.find_first_not_of(' ', right_active_op_pos + active_op_len);
        if (right_start != std::string::npos && right_start < right_sc_end) {
            auto right_end = component_.find_last_not_of(' ', right_sc_end - 1);
            if (right_end != std::string::npos && right_end >= right_start) {
                right_search_condition_ =
                        component_.substr(right_start, right_end - right_start + 1);
            }
        }
    }
}

//=======================================================

std::string Where_Clause_Normalizer::rewrite() const {
    std::stringstream result;
    result << pre_where_ << geometry_ << " " << logical_op_ << " "
           << left_search_condition_ << post_geom_parens_;
    if (!right_search_condition_.empty()) {
        result << " " << logical_op_ << " " << right_search_condition_;
    }
    return result.str();
}

//=======================================================

std::string Where_Clause_Normalizer::get_normalized_where_clause() const {
    if (!needs_rewrite_) {
        return component_;
    }
    return rewrite();
}

}  // namespace ADQL
