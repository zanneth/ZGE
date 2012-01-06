//
//  runnable_interface.h
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_RUNNABLE_INTERFACE_H_
#define _ZGE_RUNNABLE_INTERFACE_H_


namespace zge {

class ZRunnableInterface {
    unsigned _lastUpdate;
    
public:
    virtual ~ZRunnableInterface() {}
    virtual void update(unsigned dtime) = 0;
    
    friend class ZRunLoop;
};

}

#endif // _ZGE_RUNNABLE_INTERFACE_H_
