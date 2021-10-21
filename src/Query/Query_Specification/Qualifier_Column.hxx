#pragma once

#include <ostream>
#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

namespace ADQL {
class Qualifier_Column {
public:
    std::string qualifier, column;
    bool empty() const { return column.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Qualifier_Column &column) {
    os << column.qualifier << "." << column.column;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Qualifier_Column,
                          (std::string, qualifier)(std::string, column))
