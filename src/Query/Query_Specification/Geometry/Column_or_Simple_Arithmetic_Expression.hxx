#pragma once

#include <stdexcept>
#include <string>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include "../../../to_string.hxx"
#include "../Binary_Arithmetic_Expression.hxx"
#include "../Column_Reference.hxx"

namespace {

class Column_or_Simple_Arithmetic_Expression_Empty_Visitor
        : public boost::static_visitor<bool> {
public:
    bool operator()(const double &) const { return false; }
    bool operator()(const ADQL::Column_Reference &s) const { return s.empty(); }
    bool operator()(const ADQL::Binary_Arithmetic_Expression &) const { return false; }
};

class Column_or_Simple_Arithmetic_Expression_Double_Visitor
        : public boost::static_visitor<double> {
public:
    double operator()(const double &p) const { return p; }
    double operator()(const ADQL::Column_Reference &c) const {
        throw std::runtime_error("Expected a number, but got: " + ADQL::to_string(c));
    }
    double operator()(const ADQL::Binary_Arithmetic_Expression &bae) const {
        return bae.evaluate();
    }
};
}  // namespace

namespace ADQL {

class Column_or_Simple_Arithmetic_Expression {
public:
    typedef boost::variant<Binary_Arithmetic_Expression, Column_Reference, double>
            Variant;
    Variant variant;

    // We cannot use ADQL::empty_variant because double and
    // Binary_Arithmetic_Expression do not have an empty() method.

    inline bool empty() const {
        Column_or_Simple_Arithmetic_Expression_Empty_Visitor visitor;
        return boost::apply_visitor(visitor, variant);
    }
};

inline double double_or_throw(const Column_or_Simple_Arithmetic_Expression &c) {
    Column_or_Simple_Arithmetic_Expression_Double_Visitor visitor;
    return boost::apply_visitor(visitor, c.variant);
}

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Column_or_Simple_Arithmetic_Expression &c) {
    return os << c.variant;
}

}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Column_or_Simple_Arithmetic_Expression,
                          (ADQL::Column_or_Simple_Arithmetic_Expression::Variant,
                           variant))
