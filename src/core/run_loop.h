/*
 * run_loop.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/schedulable.h>
#include <zge/noncopyable.h>
#include <cstdint>
#include <chrono>
#include <vector>
#include <zprelude/zprelude.h>

ZGE_BEGIN_NAMESPACE

class ZRunloop : ZNoncopyable {
public:
    ZRunloop();
    ~ZRunloop();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZRunloop);
    
    /* Accessors */
    bool is_running() const;
    bool is_on_main_thread() const;
    
    /* Starting/Stopping the Run Loop */
    void run();
    void stop();
    
    /* Managing schedulables in the Run Loop */
    void schedule(ZSchedulableRef schedulable);
    void unschedule(ZSchedulableRef schedulable);
    
    /* Friends */
    friend class ZApplication;

private:
    void _run();
    void _main();
    
private:
    std::vector<ZSchedulableRef> _schedulables;
    zrunloop    *_runloop;
    ztimer      *_timer;
    std::mutex   _mutex;
    
    bool         _on_main_thread;
    bool         _running;
};

ZGE_DEFINE_SREF_TYPE(ZRunloop);

ZGE_END_NAMESPACE
