/*
 * noncopyable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

namespace zge {

class ZNonCopyable {
protected:
    ZNonCopyable()  = default;
    ~ZNonCopyable() = default;

private:
    ZNonCopyable(const ZNonCopyable&)                   = delete;
    const ZNonCopyable& operator=(const ZNonCopyable&)  = delete;
};

} // namespace zge
