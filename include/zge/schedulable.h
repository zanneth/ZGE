/*
 * schedulable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>

namespace zge {

typedef std::shared_ptr<class schedulable> schedulable_ref;

class schedulable {
    unsigned _last_update = 0;
    
public:
    virtual ~schedulable() {}
    virtual void run(unsigned dtime) = 0;
    
    friend class runloop;
};

} // namespace zge
