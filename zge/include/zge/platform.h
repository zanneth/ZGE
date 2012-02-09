//
//  platform.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/application.h"
#include "zge/noncopyable.h"

namespace zge {

class ZPlatform : private ZNonCopyable {
protected:
    ZApplication *_application;
    
public:
    virtual ~ZPlatform() {}
    virtual void runApplication(ZApplication *application) = 0;
};

} // namespace zge