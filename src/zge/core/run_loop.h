/*
 * run_loop.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <zge/core/defines.h>
#include <zge/core/schedulable.h>
#include <zge/core/noncopyable.h>
#include <cstdint>
#include <chrono>
#include <vector>

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
    void _main();
    
private:
    std::vector<ZSchedulableRef> _schedulables;
    bool _on_main_thread;
    bool _running;
};

ZGE_DEFINE_SREF_TYPE(ZRunloop);

ZGE_END_NAMESPACE
