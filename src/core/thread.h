/*
 * thread.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/23/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/run_loop.h>
#include <functional>
#include <thread>

ZGE_BEGIN_NAMESPACE

using ZThreadTask = std::function<void()>;

class ZThread : ZNoncopyable {
public:
    ZThread();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZThread);
    
    ZRunloopRef get_runloop() const;
    std::thread::id get_id() const;
    
    void dispatch_task(const ZThreadTask &task);
    void dispatch_task_sync(const ZThreadTask &task);
    
    void join();
    void detach();
    
private:
    ZRunloopRef _runloop;
    std::thread _thread;
};

ZGE_DEFINE_SREF_TYPE(ZThread);

ZGE_END_NAMESPACE
