#pragma once

#include "../Column_Reference.hxx"

namespace ADQL {
typedef boost::variant<std::string, Column_Reference> Sort_Key;
}
