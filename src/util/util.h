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

#define zassert(...)    util::assert_true(__VA_ARGS__)

namespace zge {
namespace util {

template <typename T>
inline T degrees_to_radians(T degrees)
{
    return degrees * (M_PI / 180.0f);
}
std::string format(const std::string &format, ...);
std::string separate_components(const std::vector<std::string> &vec, std::string delimiter);
void assert_true(bool expression, const char *format, ...) throw();

} // namespace util
} // namespace zge
