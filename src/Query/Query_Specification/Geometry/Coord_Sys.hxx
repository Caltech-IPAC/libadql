#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <iostream>

namespace ADQL {

class Coord_Sys {
public:
    enum class Reference_Frame { ICRS, J2000, Galactic } frame;
    enum class Reference_Position { GEOCENTER } position;

    Coord_Sys(Reference_Frame ref_frame = Reference_Frame::ICRS,
              Reference_Position ref_position = Reference_Position::GEOCENTER)
            : frame(ref_frame), position(ref_position) {}
};

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Coord_Sys::Reference_Frame &frame) {
    switch (frame) {
        case ADQL::Coord_Sys::Reference_Frame::J2000:
            os << "J2000";
            break;
        case ADQL::Coord_Sys::Reference_Frame::ICRS:
            os << "ICRS";
            break;
        case ADQL::Coord_Sys::Reference_Frame::Galactic:
            os << "GALACTIC";
            break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const ADQL::Coord_Sys::Reference_Position &pos) {
    switch (pos) {
        case ADQL::Coord_Sys::Reference_Position::GEOCENTER:
            os << "GEOCENTER";
            break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const ADQL::Coord_Sys &c) {
    os << c.frame;
    os << " " << c.position;
    return os;
}

}  // namespace ADQL

BOOST_FUSION_ADAPT_STRUCT(ADQL::Coord_Sys,
                          (ADQL::Coord_Sys::Reference_Frame,
                           frame)(ADQL::Coord_Sys::Reference_Position, position))
