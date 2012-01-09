//
//  run_loop.h
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_RUN_LOOP_H_
#define _ZGE_RUN_LOOP_H_

#include <memory>
#include <vector>

#include <zge/interfaces/runnable_interface.h>

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

}

#endif // _ZGE_RUN_LOOP_H_
