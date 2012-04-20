/*
 * types.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

namespace zge {

template <class T>
struct ZNullDeleter {
    void operator()(void const *) const {}
};

} // namespace zge
