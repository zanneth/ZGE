//
//  base_os_interface.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_BASE_OS_INTERFACE_H_
#define _ZGE_BASE_OS_INTERFACE_H_

#include "base_application.h"

namespace zge {

class ZBaseOSInterface {
protected:
    ZBaseApplication *_application;
    
public:
    virtual void initialize() = 0;
    
    void setApplication(ZBaseApplication *app) { _application = app; }
    ZBaseApplication* getApplication() { return _application; }
};

}

#endif
