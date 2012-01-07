//
//  application.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_APPLICATION_H_
#define _ZGE_APPLICATION_H_

#include <string>
#include <list>
#include <memory>

#include <zge/system/run_loop.h>


namespace zge {

class ZApplication {
    std::list<std::string> _arguments;
    std::auto_ptr<ZRunLoop> _mainRunLoop;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication() {}
    
    /** Accessors **/
    std::list<std::string> getArguments() { return _arguments; }
    void setArguments(int argc, char **argv);
    ZRunLoop* getMainRunLoop() { return _mainRunLoop.get(); }
    void setMainRunLoop(ZRunLoop *runLoop) { _mainRunLoop.reset(runLoop); } // Claims ownership
    
    
    /** Convenience Method for Run Loop **/
    void startMainRunLoop();
    
    
    /** Callbacks **/
    virtual void applicationReady() {}
};

void runApplication(ZApplication *application);

}

#endif // _ZGE_APPLICATION_H_
