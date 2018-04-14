/*
 * util.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */

#pragma once

#include <zge/core/foundation.h>

#define zassert(...)    zge::ZUtil::assert_true(__VA_ARGS__)

ZGE_BEGIN_NAMESPACE

class ZUtil {
public:
    // convert degrees to radians
    static inline float degrees_to_radians(float degrees);
    
    // format a stl string
    static std::string format(const char *format, ...) ZGE_FORMATARG(1, 2);
    
    // return a string representing the components of `vec` separated by `delimiter`
    static std::string join_components(const std::vector<std::string> &vec, std::string delimiter);
    
    // assertions with formatted error strings
    static void assert_true(bool expression, const char *format, ...) throw(ZException) ZGE_FORMATARG(2, 3);
    
    // return the current time
    static ZTime get_current_time();
};

ZGE_END_NAMESPACE
