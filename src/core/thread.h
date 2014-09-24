/*
 * thread.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/23/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/run_loop.h>
#include <thread>

BEGIN_ZGE_NAMESPACE

class ZThread : ZNoncopyable {
public:
    ZThread();
    
    ZRunloopRef get_runloop() const;
    std::thread::id get_id() const;
    
    void join();
    void detach();
    
private:
    ZRunloopRef _runloop;
    std::thread _thread;
};

typedef std::shared_ptr<ZThread> ZThreadRef;

END_ZGE_NAMESPACE
