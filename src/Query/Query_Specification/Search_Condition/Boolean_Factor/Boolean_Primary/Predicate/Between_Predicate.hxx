#pragma once

#include "../../../../Value_Expression_Non_Bool_Wrap.hxx"
#include "../../../../Value_Expression_Wrap.hxx"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Between_Predicate {
public:
    Value_Expression_Non_Bool_Wrap value;
    Value_Expression_Wrap low, high;
    std::string Not;
    bool empty() const { return ADQL::empty(value); }
};

std::ostream &operator<<(std::ostream &os, const ADQL::Between_Predicate &b);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Between_Predicate,
                          (ADQL::Value_Expression_Non_Bool_Wrap,
                           value)(std::string, Not)(ADQL::Value_Expression_Wrap,
                                                    low)(ADQL::Value_Expression_Wrap,
                                                         high))
