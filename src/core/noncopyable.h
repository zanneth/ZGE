/*
 * ZNoncopyable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <zge/defines.h>

ZGE_BEGIN_NAMESPACE

class ZNoncopyable {
protected:
    ZNoncopyable()  = default;
    ~ZNoncopyable() = default;

private:
    ZNoncopyable(const ZNoncopyable&)                   = delete;
    const ZNoncopyable& operator=(const ZNoncopyable&)  = delete;
};

ZGE_END_NAMESPACE
