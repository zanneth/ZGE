//
//  base_application.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_BASE_APPLICATION_H_
#define _ZGE_BASE_APPLICATION_H_

#include <string>
#include <list>

namespace zge {

class ZBaseApplication {
    std::list<std::string> _arguments;
    
public:
    ZBaseApplication(int argc, char **argv);
    
    /** Accessors **/
    std::list<std::string> getArguments() { return _arguments; }
    void setArguments(int argc, char **argv);
    
    /** Callbacks **/
    virtual void applicationReady() {}
};

void ZRunApplication(ZBaseApplication *application);

}

#endif // _ZGE_BASE_APPLICATION_H_
