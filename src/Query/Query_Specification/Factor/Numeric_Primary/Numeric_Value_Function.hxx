#pragma once

#include <boost/variant.hpp>

#include "../../Non_Predicate_Geometry_Function.hxx"
#include "../../Whitelisted_Function_Wrap.hxx"
#include "Numeric_Value_Function/Cast_Function.hxx"
#include "Numeric_Value_Function/Math_Function.hxx"
#include "Numeric_Value_Function/Position_Function.hxx"
#include "Numeric_Value_Function/Trig_Function.hxx"

namespace ADQL {
class Numeric_Value_Function {
public:
    typedef boost::variant<Trig_Function, Math_Function, Cast_Function,
                           Position_Function, Non_Predicate_Geometry_Function,
                           Whitelisted_Function_Wrap, std::string>
            Variant;
    Variant variant;
    bool empty() const;
};

std::ostream &operator<<(std::ostream &os,
                         const ADQL::Numeric_Value_Function &numeric_value_function);
}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Numeric_Value_Function,
                          (ADQL::Numeric_Value_Function::Variant, variant))
