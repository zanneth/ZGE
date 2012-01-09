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

using std::string;
using std::list;
using std::auto_ptr;


namespace zge {

class ZApplication {
    list<string> _arguments;
    auto_ptr<ZRunLoop> _mainRunLoop;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication() {}
    
    /** Accessors **/
    list<string> getArguments() const { return _arguments; }
    void setArguments(int argc, char **argv);
    ZRunLoop* getMainRunLoop();
    
    
    /** Convenience Method for Run Loop **/
    void startMainRunLoop();
    
    
    /** Callbacks **/
    virtual void applicationReady() {}
};

void runApplication(ZApplication *application);

}

#endif // _ZGE_APPLICATION_H_
