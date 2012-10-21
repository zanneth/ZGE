/*
 * schedulable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>

namespace zge {

typedef std::shared_ptr<class ZSchedulable> ZSchedulableRef;

class ZSchedulable {
    uint32_t _last_update = 0;
    
public:
    virtual ~ZSchedulable() {}
    virtual void run(uint32_t dtime) = 0;
    
    friend class ZRunloop;
};

} // namespace zge
