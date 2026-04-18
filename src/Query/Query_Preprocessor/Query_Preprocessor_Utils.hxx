#pragma once

#include <algorithm>
#include <string>

namespace ADQL::Query_Preprocessor_Utils {

//=======================================================

// Case-insensitive forward search. Returns the position of the first
// match of needle in haystack at or after pos, or npos if not found.

inline std::string::size_type case_insensitive_find(const std::string &haystack,
                                                    const std::string &needle,
                                                    std::string::size_type pos = 0) {
    auto iter = std::search(haystack.begin() + pos, haystack.end(), needle.begin(),
                            needle.end(), [](char a, char b) {
                                return std::toupper((unsigned char)a) ==
                                       std::toupper((unsigned char)b);
                            });
    if (iter == haystack.end()) {
        return std::string::npos;
    }
    return std::distance(haystack.begin(), iter);
}

//=======================================================

// Case-insensitive reverse search within [left, right).
// Returns the position of the right-most match, or npos if not found.

inline std::string::size_type case_insensitive_rfind(const std::string &haystack,
                                                     const std::string &needle,
                                                     std::string::size_type left,
                                                     std::string::size_type right) {
    auto it = std::search(haystack.crbegin() + (haystack.size() - right),
                          haystack.crbegin() + (haystack.size() - left),
                          needle.crbegin(), needle.crend(), [](char a, char b) {
                              return std::tolower((unsigned char)a) ==
                                     std::tolower((unsigned char)b);
                          });
    if (it == haystack.crbegin() + (haystack.size() - left)) {
        return std::string::npos;
    }
    return std::distance(haystack.cbegin(), it.base()) - needle.size();
}

//=======================================================

// Returns true if pos is at a word boundary, i.e. the character
// immediately before pos is neither alphanumeric nor '_'.

inline bool is_word_boundary_left(const std::string &input,
                                  std::string::size_type pos) {
    if (pos == 0) {
        return true;
    }
    char c = input[pos - 1];
    return !std::isalnum((unsigned char)c) && c != '_';
}

//=======================================================

// Finds the first occurrence of keyword in input at or after pos that
// is at a left word boundary. Returns npos if not found.  Use this to
// guard against false positive matches, e.g. matches for ST_Contains
// when searching case-insensitively for CONTAINS.

inline std::string::size_type find_keyword(const std::string &input,
                                           const std::string &keyword,
                                           std::string::size_type pos = 0) {
    while (pos < input.size()) {
        auto found = case_insensitive_find(input, keyword, pos);
        if (found == std::string::npos) {
            return std::string::npos;
        }
        if (is_word_boundary_left(input, found)) {
            return found;
        }
        pos = found + keyword.size();
    }
    return std::string::npos;
}

//=======================================================

// Checks for CONTAINS and INTERSECTS positions in input starting at pos.
// Throws if both are present.
// Returns false if neither is present, true otherwise.
inline bool check_for_geometry_keywords(const std::string &input,
                                        std::string::size_type pos,
                                        std::string::size_type &contains_pos,
                                        std::string::size_type &intersects_pos) {
    contains_pos = find_keyword(input, "CONTAINS", pos);
    intersects_pos = find_keyword(input, "INTERSECTS", pos);
    if (contains_pos != std::string::npos && intersects_pos != std::string::npos) {
        throw std::runtime_error("Query must not invoke both CONTAINS and INTERSECTS.");
    }
    return contains_pos != std::string::npos || intersects_pos != std::string::npos;
}

}  // namespace ADQL::Query_Preprocessor_Utils
