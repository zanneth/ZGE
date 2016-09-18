//
//  schedulable.cpp
//  ZGE
//
//  Created by Charles Magahern on 9/23/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#include "schedulable.h"
#include "run_loop.h"

ZGE_BEGIN_NAMESPACE

ZSchedulable::ZSchedulable() :
    _unschedule_after_run(false)
{}

bool ZSchedulable::unschedule_after_run() const { return _unschedule_after_run; }

void ZSchedulable::set_unschedule_after_run(bool unschedule_after_run) { _unschedule_after_run = unschedule_after_run; }

#pragma mark - ZWorkSchedulable

ZWorkSchedulable::ZWorkSchedulable(std::function<void(uint32_t)> work) :
    _work(work)
{}

void ZWorkSchedulable::run(uint32_t dtime)
{
    _work(dtime);
}

ZGE_END_NAMESPACE
