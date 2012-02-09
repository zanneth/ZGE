//
//  run_loop.h
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/runnable_interface.h"
#include "zge/noncopyable.h"

#include <memory>
#include <vector>

namespace zge {

using std::vector;

class ZRunLoop : private ZNonCopyable {
    vector<ZRunnableInterfaceRef> _runnables;
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