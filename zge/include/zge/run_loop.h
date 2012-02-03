//
//  run_loop.h
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/runnable_interface.h"

#include <memory>
#include <vector>

namespace zge {
using std::vector;
using std::shared_ptr;

class ZRunLoop {
    vector<shared_ptr<ZRunnableInterface>> _runnables;
    bool _running;
    
public:
    ZRunLoop();
    ~ZRunLoop();
    
    /** Accessors **/
    bool isRunning() { return _running; }
    
    
    /** Starting the Run Loop **/
    void run();
    
    
    /** Managing Runnables in the Run Loop **/
    void schedule(shared_ptr<ZRunnableInterface> runnable);
    void unschedule(shared_ptr<ZRunnableInterface> runnable);

private:
    void _main();
};

} // namespace zge