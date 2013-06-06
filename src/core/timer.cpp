/*
 * timer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/06/2013
 */

#include "timer.h"
#include <zge/run_loop.h>
#include <SDL2/SDL.h>

namespace zge {

ZTimer::ZTimer(const ZTimerFunction &func) :
    _function(func),
    _repeats(true),
    _time_scheduled(0),
    _time_last_fired(0)
{}

ZTimer::~ZTimer()
{}

#pragma mark - Accessors

void ZTimer::set_function(const ZTimerFunction &function)
{
    _function = function;
}

uint32_t ZTimer::get_interval() const
{
    return _interval;
}

void ZTimer::set_interval(const uint32_t interval)
{
    _interval = interval;
}

bool ZTimer::get_repeats() const
{
    return _repeats;
}
    
void ZTimer::set_repeats(bool repeats)
{
    _repeats = repeats;
}

#pragma mark - Overrides

void ZTimer::run(uint32_t dtime)
{
    uint32_t time = SDL_GetTicks();
    uint32_t time_delta = 0;
    
    if (_time_last_fired == 0) {
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

} // namespace zge
