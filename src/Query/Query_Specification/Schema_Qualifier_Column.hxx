#pragma once

#include <ostream>
#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

namespace ADQL {
class Schema_Qualifier_Column {
public:
    std::string schema, qualifier, column;
    bool empty() const { return column.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Schema_Qualifier_Column &s) {
    os << s.schema << "." << s.qualifier << "." << s.column;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Schema_Qualifier_Column,
                          (std::string, schema)(std::string, qualifier)(std::string,
                                                                        column))
