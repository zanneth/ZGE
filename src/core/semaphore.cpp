//
//  semaphore.cpp
//  ZGE
//
//  Created by Charles Magahern on 9/23/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#include "semaphore.h"

ZGE_BEGIN_NAMESPACE

ZSemaphore::ZSemaphore(int64_t value) :
    _value(value),
    _max(value ?: 1)
{}

ZSemaphore::~ZSemaphore()
{}

void ZSemaphore::signal()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_value < _max) {
        ++_value;
    }
    _condition.notify_one();
}

void ZSemaphore::wait()
{
    std::unique_lock<std::mutex> lock(_mutex);
    while (_value == 0) {
        _condition.wait(lock);
    }
    --_value;
}

ZGE_END_NAMESPACE
