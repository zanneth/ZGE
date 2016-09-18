/*
 * timer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/06/2013
 */

#include "timer.h"
#include <chrono>
#include <zge/core/run_loop.h>

ZGE_BEGIN_NAMESPACE

ZTimer::ZTimer(const ZTimerFunction &func) :
    _function(func),
    _repeats(false),
    _valid(false)
{}

ZTimer::~ZTimer()
{}

#pragma mark - Accessors

void ZTimer::set_function(const ZTimerFunction &function) { _function = function; }

ZTimeInterval ZTimer::get_interval() const { return _interval; }
void ZTimer::set_interval(ZTimeInterval interval) { _interval = interval; }

bool ZTimer::repeats() const { return _repeats; }
void ZTimer::set_repeats(bool repeats) { _repeats = repeats; }

#pragma mark - Overrides

void ZTimer::run(uint32_t dtime)
{
    if (_valid) {
        using namespace std::chrono;
        
        ZTime time = ZUtil::get_current_time();
        ZTimeInterval time_delta;
        
        if (_time_last_fired == ZTime()) {
            time_delta = time - _time_scheduled;
        } else {
            time_delta = time - _time_last_fired;
        }
        
        if (time_delta >= _interval) {
            fire();
            
            if (!_repeats) {
                invalidate();
            }
        }
    }
}

void ZTimer::on_schedule()
{
    _time_scheduled = ZUtil::get_current_time();
    _valid = true;
}

#pragma mark - API Functions
    
void ZTimer::fire()
{
    _function(shared_from_this());
    _time_last_fired = ZUtil::get_current_time();
}

void ZTimer::invalidate()
{
    if (_run_loop != nullptr) {
        ZSchedulableRef scheduled = shared_from_this();
        _run_loop->unschedule(scheduled);
    }
    
    _valid = false;
}

ZGE_END_NAMESPACE
