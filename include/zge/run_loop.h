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

class ZRunLoop : ZNonCopyable {
    std::vector<ZSchedulableRef> _ZSchedulables;
    bool _running;
    bool _onMainThread;
    
public:
    ZRunLoop();
    ~ZRunLoop();
    
    /** Accessors **/
    bool isRunning() { return _running; }
    bool isOnMainThread() { return _onMainThread; }
    
    /** Starting/Stopping the Run Loop **/
    void run();
    void stop();
    
    /** Managing ZSchedulables in the Run Loop **/
    void schedule(ZSchedulableRef ZSchedulable);
    void unschedule(ZSchedulableRef ZSchedulable);
    
    /** Friends **/
    friend class ZApplication;

private:
    void _main();
};

} // namespace zge
