#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <iostream>
#include <limits>
#include <string>

namespace ADQL {

class Binary_Arithmetic_Expression {
public:
    char operation;
    double arg0, arg1;

    inline double evaluate() const {
        switch (operation) {
            case '+':
                return arg0 + arg1;
            case '-':
                return arg0 - arg1;
            case '*':
                return arg0 * arg1;
                break;
            case '/':
                if (arg1 == 0.0) {
                    throw std::runtime_error("Denominator must not be 0.");
                }
                return arg0 / arg1;
                break;
            default:
                throw std::runtime_error("unknown operator.");
        }
    }

};  // namespace ADQL

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Binary_Arithmetic_Expression &bae) {
    // Write every significant digit of the operands and put spaces
    // around the operator so that a negative second operand does
    //  not produce "--", the start of a comment in SQL.
    const auto old_precision = os.precision(std::numeric_limits<double>::max_digits10);
    os << bae.arg0 << ' ' << bae.operation << ' ' << bae.arg1;
    os.precision(old_precision);
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Binary_Arithmetic_Expression,
                          (double, arg0)(char, operation)(double, arg1))
