/*
 * schedulable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>
#include <zge/foundation.h>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZSchedulable> ZSchedulableRef;
class ZRunloop;

class ZSchedulable {
protected:
    ZTime _last_update;
    ZRunloop *_run_loop = nullptr; // weak
    
public:
    virtual ~ZSchedulable() {}
    virtual void run(uint32_t dtime) = 0;
    
    // Callbacks from the runloop.
    virtual void on_schedule() {}
    virtual void on_unschedule() {}
    
    friend class ZRunloop;
};

END_ZGE_NAMESPACE
