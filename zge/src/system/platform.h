//
//  platform.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_PLATFORM_H_
#define _ZGE_PLATFORM_H_

#include <zge/system/application.h>


namespace zge {

class ZPlatform {
protected:
    ZApplication *_application;
    
public:
    virtual ~ZPlatform() {}
    virtual void initialize() = 0;
    
    void setApplication(ZApplication *application) { _application = application; } // Weak Ptr
    ZApplication* getApplication() { return _application; }
};

}

#endif // _ZGE_PLATFORM_H_
