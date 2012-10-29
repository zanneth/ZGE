/*
 * util.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */

#pragma once

#include <cmath>
#include <string>

#define zassert(...)    util::assert_true(__VA_ARGS__)

namespace zge {
namespace util {

template <typename T>
static inline T degrees_to_radians(T degrees)
{
    return degrees * (M_PI / 180.0f);
}
static std::string format(const std::string &format, ...);
static void assert_true(bool expression, const char *format, ...) throw();

} // namespace util
} // namespace zge
