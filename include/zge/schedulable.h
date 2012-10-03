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
    unsigned _last_update = 0;
    
public:
    virtual ~ZSchedulable() {}
    virtual void run(unsigned dtime) = 0;
    
    friend class ZRunloop;
};

} // namespace zge
