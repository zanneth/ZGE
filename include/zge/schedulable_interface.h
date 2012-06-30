/*
 * schedulable_interface.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>

namespace zge {

typedef std::shared_ptr<class ZSchedulableInterface> ZSchedulableRef;

class ZSchedulableInterface {
    unsigned _lastUpdate;
    
public:
    virtual ~ZSchedulableInterface() {}
    virtual void run(unsigned dtime) = 0;
    
    friend class ZRunLoop;
};

} // namespace zge
