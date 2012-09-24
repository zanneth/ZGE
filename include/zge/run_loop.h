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

class ZRunloop : ZNoncopyable {
    std::vector<ZSchedulableRef> _schedulables;
    bool _running;
    bool _on_main_thread;
    
public:
    ZRunloop();
    ~ZRunloop();
    
    /** Accessors **/
    bool is_running() { return _running; }
    bool is_on_main_thread() { return _on_main_thread; }
    
    /** Starting/Stopping the Run Loop **/
    void run();
    void stop();
    
    /** Managing schedulables in the Run Loop **/
    void schedule(ZSchedulableRef schedulable);
    void unschedule(ZSchedulableRef schedulable);
    
    /** Friends **/
    friend class ZApplication;

private:
    void _main();
};

} // namespace zge
