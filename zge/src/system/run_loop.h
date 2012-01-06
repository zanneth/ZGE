//
//  run_loop.h
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_RUN_LOOP_H_
#define _ZGE_RUN_LOOP_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include <zge/interfaces/runnable_interface.h>

using std::vector;
using boost::shared_ptr;


namespace zge {

typedef vector< shared_ptr<ZRunnableInterface> >::iterator RunnableIterator;

class ZRunLoop {
    vector< shared_ptr<ZRunnableInterface> > _runnables;
    bool _running;
    
public:
    ZRunLoop();
    ~ZRunLoop();
    
    /** Accessors **/
    bool isRunning() { return _running; }
    
    
    /** Starting the Run Loop **/
    void run();
    
    
    /** Managing Runnables in the Run Loop **/
    void schedule(boost::shared_ptr<ZRunnableInterface> runnable);
    void unschedule(boost::shared_ptr<ZRunnableInterface> runnable);

private:
    void _startRunLoop();
};

}

#endif // _ZGE_RUN_LOOP_H_
