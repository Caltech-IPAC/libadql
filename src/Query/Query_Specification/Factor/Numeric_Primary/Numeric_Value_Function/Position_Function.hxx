#pragma once

#include <iostream>
#include <string>

#include "../../../Column_Reference.hxx"

namespace ADQL {
class Position_Function {
public:
  std::string substring;
  Column_Reference column_reference;
    bool empty() const { return column_reference.empty(); }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Position_Function &position_function) {
  os << "POSITION(" << position_function.substring
	 << " IN " << position_function.column_reference
	   << ")";
    return os;
}
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Position_Function,
						  (std::string, substring)(ADQL::Column_Reference, column_reference))
