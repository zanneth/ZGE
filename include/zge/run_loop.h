/*
 * run_loop.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/schedulable.h"
#include "zge/noncopyable.h"

#include <memory>
#include <vector>

namespace zge {

class runloop : noncopyable {
    std::vector<schedulable_ref> _schedulables;
    bool _running;
    bool _on_main_thread;
    
public:
    runloop();
    ~runloop();
    
    /** Accessors **/
    bool is_running() { return _running; }
    bool is_on_main_thread() { return _on_main_thread; }
    
    /** Starting/Stopping the Run Loop **/
    void run();
    void stop();
    
    /** Managing schedulables in the Run Loop **/
    void schedule(schedulable_ref schedulable);
    void unschedule(schedulable_ref schedulable);
    
    /** Friends **/
    friend class application;

private:
    void _main();
};

} // namespace zge
