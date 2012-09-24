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

class application;

class platform : noncopyable {
public:
    virtual ~platform() {}
    
    virtual std::string get_description();
    virtual void run_application(application *application) = 0;
};

} // namespace zge
