/*
 * run_loop.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <cstdint>
#include <zge/defines.h>
#include <zge/schedulable.h>
#include <zge/noncopyable.h>
#include <vector>

BEGIN_ZGE_NAMESPACE

class ZRunloop : ZNoncopyable {
public:
    ZRunloop();
    ~ZRunloop();
    
    /* Accessors */
    bool is_running() { return _running; }
    bool is_on_main_thread() { return _on_main_thread; }
    
    /* Starting/Stopping the Run Loop */
    void run();
    void stop();
    
    /* Managing schedulables in the Run Loop */
    void schedule(ZSchedulableRef schedulable);
    void unschedule(ZSchedulableRef schedulable);
    
    /* Friends */
    friend class ZApplication;

private:
    void _main();
    
private:
    std::vector<ZSchedulableRef> _schedulables;
    bool _running;
    bool _on_main_thread;
    std::mutex _mutex;
};

typedef std::shared_ptr<ZRunloop> ZRunloopRef;

END_ZGE_NAMESPACE
