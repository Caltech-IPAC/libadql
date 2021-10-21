#pragma once

#include "Simple_Whens/Simple_When.hxx"

namespace ADQL {
using Simple_Whens = std::vector<Simple_When>;

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Simple_Whens &simple_whens) {
    for (auto &when : simple_whens) {
        os << when << " ";
    }
    return os;
}
}  // namespace ADQL
