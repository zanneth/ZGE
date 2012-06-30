/*
 * platform.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include <string>

namespace zge {

class ZApplication;

class ZPlatform : ZNonCopyable {
public:
    virtual ~ZPlatform() {}
    
    virtual std::string getDescription();
    virtual void runApplication(ZApplication *application) = 0;
};

} // namespace zge
