/*
 * util.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */

#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <zge/geometry.h>

#define zassert(...)    ZUtil::assert_true(__VA_ARGS__)

namespace zge {

class ZUtil {
public:
    // convert degrees to radians
    static inline float degrees_to_radians(float degrees);
    
    // format a stl string
    static std::string format(const std::string &format, ...);
    
    // return a string representing the components of `vec` separated by `delimiter`
    static std::string separate_components(const std::vector<std::string> &vec, std::string delimiter);
    
    // assertions with formatted error strings
    static void assert_true(bool expression, const char *format, ...) throw();
};

} // namespace zge
