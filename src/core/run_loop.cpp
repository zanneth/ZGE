/*
 * run_loop.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/run_loop.h>

#include <algorithm>
#include <SDL2/SDL.h>

namespace zge {

ZRunloop::ZRunloop() :
    _running(false)
{}

ZRunloop::~ZRunloop()
{
    _running = false;
}

#pragma mark - Starting the Run Loop

void ZRunloop::run()
{
    _running = true;
    _main();
}

void ZRunloop::stop()
{
    _running = false;
}

#pragma mark - Managing schedulables in the Run Loop

void ZRunloop::schedule(ZSchedulableRef schedulable)
{
    schedulable->_run_loop = this;
    schedulable->on_schedule();
    
    _schedulables.push_back(schedulable);
}

void ZRunloop::unschedule(ZSchedulableRef schedulable)
{
    auto itr = std::find(_schedulables.begin(), _schedulables.end(), schedulable);
    if (itr != _schedulables.end()) {
        schedulable->on_unschedule();
        
        schedulable->_run_loop = nullptr;
        _schedulables.erase(itr);
    }
}

#pragma mark - Private Methods

void ZRunloop::_main()
{
    while (_running) {
        for (ZSchedulableRef schedulable : _schedulables) {
            uint32_t time = SDL_GetTicks();
            uint32_t last_update = schedulable->_last_update;
            uint32_t dtime;
            
            if (last_update == 0) {
                dtime = 0;
            } else {
                dtime = time - last_update;
            }
            
            schedulable->run(dtime);
            schedulable->_last_update = time;
        }
        
        // very naive timing mechanism.
        SDL_Delay(1);
    }
}

} // namespace zge
