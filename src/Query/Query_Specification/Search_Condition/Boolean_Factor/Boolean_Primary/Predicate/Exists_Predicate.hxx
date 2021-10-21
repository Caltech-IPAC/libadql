#pragma once

#include "../../../../../Subquery_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Exists_Predicate {
public:
    Subquery_Wrap subquery;
    bool empty() const { return ADQL::empty(subquery); }
};

std::ostream &operator<<(std::ostream &os, const ADQL::Exists_Predicate &c);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Exists_Predicate, (ADQL::Subquery_Wrap, subquery))
