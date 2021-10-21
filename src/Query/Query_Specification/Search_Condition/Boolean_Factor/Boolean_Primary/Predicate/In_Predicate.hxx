#pragma once

#include "../../../../../Subquery_Wrap.hxx"
#include "../../../../Value_Expression_Non_Bool_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>

#include <iostream>
#include <vector>

namespace ADQL {
class Value_Expression;
class In_Predicate {
public:
    Value_Expression_Non_Bool_Wrap value;
    std::string Not;

    typedef boost::variant<Subquery_Wrap, std::vector<Value_Expression> > Variant;
    Variant variant;
    bool empty() const { return ADQL::empty(value); }
};

std::ostream &operator<<(std::ostream &os, const ADQL::In_Predicate &p);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::In_Predicate,
                          (ADQL::Value_Expression_Non_Bool_Wrap,
                           value)(std::string, Not)(ADQL::In_Predicate::Variant,
                                                    variant))
