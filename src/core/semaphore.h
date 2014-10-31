//
//  semaphore.h
//  ZGE
//
//  Created by Charles Magahern on 9/23/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#pragma once

#include <zge/foundation.h>
#include <thread>

ZGE_BEGIN_NAMESPACE

class ZSemaphore {
public:
    ZSemaphore(int64_t value);
    ~ZSemaphore();
    
    void signal();
    void wait();
    
private:
    std::mutex _mutex;
    std::condition_variable _condition;
    int64_t _value;
    int64_t _max;
};

ZGE_END_NAMESPACE
