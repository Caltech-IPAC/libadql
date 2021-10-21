#pragma once

#include "../../../../../Search_Condition_Wrap.hxx"
#include "../../../Result.hxx"

namespace ADQL {
class Searched_When {
public:
    Search_Condition_Wrap wrap;
    Result result;
    bool empty() const { return result.empty(); }
};

std::ostream &operator<<(std::ostream &os, const ADQL::Searched_When &searched_when);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Searched_When,
                          (ADQL::Search_Condition_Wrap, wrap)(ADQL::Result, result))
