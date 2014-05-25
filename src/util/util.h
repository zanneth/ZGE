/*
 * util.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */

#pragma once

#include <zge/foundation.h>

#define zassert(...)    zge::ZUtil::assert_true(__VA_ARGS__)

BEGIN_ZGE_NAMESPACE

class ZUtil {
public:
    // convert degrees to radians
    static inline float degrees_to_radians(float degrees);
    
    // format a stl string
    static std::string format(const char *format, ...) ZFORMATARG(1, 2);
    
    // return a string representing the components of `vec` separated by `delimiter`
    static std::string separate_components(const std::vector<std::string> &vec, std::string delimiter);
    
    // assertions with formatted error strings
    static void assert_true(bool expression, const char *format, ...) throw() ZFORMATARG(2, 3);
    
    // return the current time
    static ZTime get_current_time();
};

END_ZGE_NAMESPACE
