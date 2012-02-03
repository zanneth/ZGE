//
//  runnable_interface.h
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

namespace zge {

class ZRunnableInterface {
    unsigned _lastUpdate;
    
public:
    virtual ~ZRunnableInterface() {}
    virtual void run(unsigned dtime) = 0;
    
    friend class ZRunLoop;
};

} // namespace zge