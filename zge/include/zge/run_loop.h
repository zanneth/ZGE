/*
 * run_loop.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/schedulable_interface.h"
#include "zge/noncopyable.h"

#include <memory>
#include <vector>

namespace zge {

class ZRunLoop : ZNonCopyable {
    std::vector<ZSchedulableRef> _schedulables;
    bool _running;
    
public:
    ZRunLoop();
    ~ZRunLoop();
    
    /** Accessors **/
    bool isRunning() { return _running; }
    
    /** Starting the Run Loop **/
    void run();
    
    /** Managing schedulables in the Run Loop **/
    void schedule(ZSchedulableRef schedulable);
    void unschedule(ZSchedulableRef schedulable);

private:
    void _main();
};

} // namespace zge
