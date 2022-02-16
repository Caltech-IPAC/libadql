#pragma once

#include "Geometry/Contains.hxx"
#include "Geometry/Intersects.hxx"

namespace ADQL {

class Geometry {
public:
    typedef boost::variant<Intersects, Contains> Predicate;

    struct Geometry_Left {
        char char_flag;
        Predicate predicate;
        bool empty() const { return empty_variant(predicate); }
    };

    struct Geometry_Right {
        Predicate predicate;
        char char_flag;
        bool empty() const { return empty_variant(predicate); }
    };

    typedef boost::variant<Geometry_Left, Geometry_Right> Variant;
    Variant variant;

    bool empty() const { return empty_variant(variant); }

    class Geometry_Predicate_Visitor
            : public boost::static_visitor<const ADQL::Geometry::Predicate &> {
    public:
        const ADQL::Geometry::Predicate &operator()(
                const ADQL::Geometry::Geometry_Left &left) const {
            return left.predicate;
        }

        const ADQL::Geometry::Predicate &operator()(
                const ADQL::Geometry::Geometry_Right &right) const {
            return right.predicate;
        }
    };

    inline const Geometry::Predicate &get_predicate() const {
        Geometry_Predicate_Visitor visitor;
        return boost::apply_visitor(visitor, variant);
    }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Geometry::Geometry_Left &left) {
    if (!left.empty()) {
        os << left.predicate << "=" << left.char_flag;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Geometry::Geometry_Right &right) {
    if (!right.empty()) {
        os << right.predicate << "=" << right.char_flag;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const ADQL::Geometry &geometry) {
    if (!geometry.empty()) {
        os << geometry.variant;
    }
    return os;
}

}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Geometry::Geometry_Left,
                          (char, char_flag)(ADQL::Geometry::Predicate, predicate))

BOOST_FUSION_ADAPT_STRUCT(ADQL::Geometry::Geometry_Right,
                          (ADQL::Geometry::Predicate, predicate)(char, char_flag))

BOOST_FUSION_ADAPT_STRUCT(ADQL::Geometry, (ADQL::Geometry::Variant, variant))
