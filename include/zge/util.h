/*
 * util.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <cmath>

namespace zge {

class ZUtil {
public:
    template <typename T>
    static inline T degrees_to_radians(T degrees)
    {
        return degrees * (M_PI / 180.0f);
    }
};

} // namespace zge
