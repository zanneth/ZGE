//
//  schedulable.cpp
//  ZGE
//
//  Created by Charles Magahern on 9/23/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#include "schedulable.h"
#include "run_loop.h"

BEGIN_ZGE_NAMESPACE

ZWorkSchedulable::ZWorkSchedulable(std::function<void()> work) :
    _work(work)
{}

void ZWorkSchedulable::run(uint32_t dtime)
{
    _work();
    
    if (_run_loop) {
        _run_loop->unschedule(shared_from_this());
    }
}

END_ZGE_NAMESPACE
