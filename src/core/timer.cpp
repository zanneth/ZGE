/*
 * timer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/06/2013
 */

#include "timer.h"
#include <chrono>
#include <zge/run_loop.h>
#include <SDL2/SDL.h>

BEGIN_ZGE_NAMESPACE

ZTimer::ZTimer(const ZTimerFunction &func) :
    _function(func),
    _repeats(false),
    _time_scheduled(0),
    _time_last_fired(0)
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
    using namespace std::chrono;
    
    uint32_t time = SDL_GetTicks();
    uint32_t time_delta = 0;
    
    if (_time_last_fired == 0) {
        time_delta = time - _time_scheduled;
    } else {
        time_delta = time - _time_last_fired;
    }
    
    uint32_t interval_millis = duration_cast<milliseconds>(_interval).count();
    if (time_delta >= interval_millis) {
        fire();
        
        if (!_repeats) {
            invalidate();
        }
    }
}

void ZTimer::on_schedule()
{
    _time_scheduled = SDL_GetTicks();
}

#pragma mark - API Functions
    
void ZTimer::fire()
{
    _function(shared_from_this());
    _time_last_fired = SDL_GetTicks();
}

void ZTimer::invalidate()
{
    if (_run_loop != nullptr) {
        ZSchedulableRef scheduled = shared_from_this();
        _run_loop->unschedule(scheduled);
    }
}

END_ZGE_NAMESPACE
