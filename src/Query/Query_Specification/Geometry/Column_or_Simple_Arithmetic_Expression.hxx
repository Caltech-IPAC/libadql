#pragma once

#include <stdexcept>
#include <string>

#include <boost/variant.hpp>

#include "../../../to_string.hxx"
#include "../Binary_Arithmetic_Expression.hxx"
#include "../Column_Reference.hxx"

namespace ADQL {
typedef boost::variant<Column_Reference, Binary_Arithmetic_Expression, double>
        Column_or_Simple_Arithmetic_Expression;

class Column_or_Simple_Arithmetic_Expression_empty_Visitor
        : public boost::static_visitor<bool> {
public:
    bool operator()(const double &) const { return false; }
    bool operator()(const Column_Reference &s) const { return s.empty(); }
    bool operator()(const Binary_Arithmetic_Expression &) const { return false; }
};

class Column_or_Simple_Arithmetic_Expression_double_Visitor
        : public boost::static_visitor<double> {
public:
    double operator()(const double &p) const { return p; }

    double operator()(const Column_Reference &c) const {
        throw std::runtime_error("Expected a number, but got: " + ADQL::to_string(c));
    }

    double operator()(const Binary_Arithmetic_Expression &bae) const {
        return bae.evaluate();
    }
};

inline double double_or_throw(const Column_or_Simple_Arithmetic_Expression &c) {
    Column_or_Simple_Arithmetic_Expression_double_Visitor visitor;
    return boost::apply_visitor(visitor, c);
}
}  // namespace ADQL
