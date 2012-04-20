/*
 * run_loop.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/runnable_interface.h"
#include "zge/noncopyable.h"

#include <memory>
#include <vector>

namespace zge {

class ZRunLoop : private ZNonCopyable {
    std::vector<ZRunnableInterfaceRef> _runnables;
    bool _running;
    
public:
    ZRunLoop();
    ~ZRunLoop();
    
    /** Accessors **/
    bool isRunning() { return _running; }
    
    
    /** Starting the Run Loop **/
    void run();
    
    
    /** Managing Runnables in the Run Loop **/
    void schedule(ZRunnableInterfaceRef runnable);
    void unschedule(ZRunnableInterfaceRef runnable);

private:
    void _main();
};

} // namespace zge
