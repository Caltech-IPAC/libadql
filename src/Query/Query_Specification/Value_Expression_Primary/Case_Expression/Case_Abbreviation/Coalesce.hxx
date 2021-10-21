#pragma once

#include "../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Coalesce {
public:
    std::vector<Value_Expression_Wrap> wraps;
    bool empty() const { return wraps.empty(); }
};

std::ostream &operator<<(std::ostream &os, const ADQL::Coalesce &coalesce);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Coalesce,
                          (std::vector<ADQL::Value_Expression_Wrap>, wraps))
