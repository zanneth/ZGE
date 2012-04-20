/*
 * platform.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/application.h"
#include "zge/noncopyable.h"

namespace zge {

class ZPlatform : private ZNonCopyable {
protected:
    ZApplication *_application;
    
public:
    virtual ~ZPlatform() {}
    virtual void runApplication(ZApplication *application) = 0;
};

} // namespace zge
