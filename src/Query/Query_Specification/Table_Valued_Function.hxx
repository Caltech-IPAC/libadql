#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>

namespace ADQL {
class Table_Valued_Function {
public:
    std::string function_name;
  std::vector<std::string> args;
    bool empty() const { return function_name.empty(); }
};

inline std::ostream &operator<<(
        std::ostream &os, const ADQL::Table_Valued_Function &table_valued_function) {
  os << "table(" << table_valued_function.function_name << '(';
    for (auto a = table_valued_function.args.begin();
         a != table_valued_function.args.end();) {
	  os << '\''<< *a << '\'';
        ++a;
        if (a != table_valued_function.args.end()) {
            os << ',';
        }
    }
    os << "))";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Table_Valued_Function,
                          (std::string, function_name)(std::vector<std::string>,
                                                  args))
