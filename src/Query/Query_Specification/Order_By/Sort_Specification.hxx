#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

#include "Sort_Key.hxx"

namespace ADQL {
class Sort_Specification {
public:
    ADQL::Sort_Key key;
    std::string ordering;
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Sort_Specification &sort_specification) {
    os << sort_specification.key;
    if (!sort_specification.ordering.empty()) {
        os << " " << sort_specification.ordering;
    }
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Sort_Specification,
                          (ADQL::Sort_Key, key)(std::string, ordering))
