#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <iostream>
#include <string>

#include "../Join_Suffix_Wrap.hxx"
#include "Correlation_Join/Table_Correlation.hxx"

namespace ADQL {
class Correlation_Join {
public:
    Table_Correlation table_correlation;
    Join_Suffix_Wrap join_suffix;

    bool empty() const { return table_correlation.empty(); }
};

inline std::ostream &operator<<(std::ostream &os, const ADQL::Correlation_Join &t) {
    os << t.table_correlation << " ";
    if (!empty(t.join_suffix)) os << t.join_suffix;
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Correlation_Join,
                          (ADQL::Table_Correlation,
                           table_correlation)(ADQL::Join_Suffix, join_suffix))
