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
#include <boost/shared_ptr.hpp>

#include <zge/system/run_loop.h>


namespace zge {

class ZApplication {
    std::list<std::string> _arguments;
    boost::shared_ptr<ZRunLoop> _mainRunLoop;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication() {}
    
    /** Accessors **/
    std::list<std::string> getArguments() { return _arguments; }
    void setArguments(int argc, char **argv);
    boost::shared_ptr<ZRunLoop> getMainRunLoop() { return _mainRunLoop; }
    void setMainRunLoop(boost::shared_ptr<ZRunLoop> runLoop) { _mainRunLoop = runLoop; }
    
    
    /** Convenience Method for Run Loop **/
    void startMainRunLoop();
    
    
    /** Callbacks **/
    virtual void applicationReady() {}
};

void runApplication(ZApplication *application);

}

#endif // _ZGE_APPLICATION_H_
