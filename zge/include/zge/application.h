//
//  application.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/run_loop.h"
#include "zge/exception.h"

#include <string>
#include <list>
#include <memory>

namespace zge {

using std::string;
using std::list;
using std::auto_ptr;

class ZApplicationException : public ZException {
public:
    virtual const char* what() const throw()
    {
        return ("An application error occurred: " + description).c_str();
    }
};

class ZApplication {
    list<string> _arguments;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication() {}
    
    /** Accessors **/
    list<string> getArguments() const { return _arguments; }
    void setArguments(int argc, char **argv);
    
    
    /** Accessing the Main Run Loop **/
    static ZRunLoop* getMainRunLoop();
    void startMainRunLoop();
    
    
    /** Callbacks **/
    virtual void applicationReady() {}
};

void runApplication(ZApplication *application);

} // namespace zge