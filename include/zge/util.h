/*
 * util.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */

#pragma once

#include <cmath>

#define zassert(...)    ZUtil::assert_true(__VA_ARGS__)

namespace zge {

class ZUtil {
public:
    template <typename T>
    static inline T degrees_to_radians(T degrees)
    {
        return degrees * (M_PI / 180.0f);
    }
    
    static std::string format_string(const std::string &format, ...);
    
    static void assert_true(bool expression, const char *format, ...) throw();
};

} // namespace zge
