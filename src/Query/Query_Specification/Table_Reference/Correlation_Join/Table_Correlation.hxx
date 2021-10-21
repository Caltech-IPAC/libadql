#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <iostream>
#include <string>

namespace ADQL {
class Table_Correlation {
public:
    std::string name, as;
    bool empty() const { return name.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Table_Correlation &table) {
    os << table.name;
    if (!table.as.empty()) os << " " << table.as;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Table_Correlation, (std::string, name)(std::string, as))
