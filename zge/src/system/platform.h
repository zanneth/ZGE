//
//  platform.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_PLATFORM_H_
#define _ZGE_PLATFORM_H_

#include <memory>
#include <zge/system/application.h>

using std::auto_ptr;


namespace zge {

class ZPlatform {
protected:
    auto_ptr<ZApplication> _application;
    
public:
    virtual ~ZPlatform() {}
    virtual void initialize() = 0;
    
    void setApplication(ZApplication *application) { _application.reset(application); } // Claims ownership
    ZApplication* getApplication() { return _application.get(); }
};

}

#endif // _ZGE_PLATFORM_H_
