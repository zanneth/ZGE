/*
 * noncopyable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

namespace zge {

class noncopyable {
protected:
    noncopyable()  = default;
    ~noncopyable() = default;

private:
    noncopyable(const noncopyable&)                   = delete;
    const noncopyable& operator=(const noncopyable&)  = delete;
};

} // namespace zge
