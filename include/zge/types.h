/*
 * types.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

namespace zge {

typedef unsigned ZUUID;

template <class T>
struct ZNullDeleter {
    void operator()(void const *) {}
};

} // namespace zge