/*
 * run_loop.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/run_loop.h"

#include <algorithm>
#include <iostream>
#include <SDL/SDL.h>

namespace zge {

runloop::runloop() :
    _running(false) {}

runloop::~runloop()
{
    _running = false;
}


#pragma mark - Starting the Run Loop

void runloop::run()
{
    _running = true;
    _main();
}

void runloop::stop()
{
    _running = false;
}


#pragma mark - Managing schedulables in the Run Loop

void runloop::schedule(schedulable_ref schedulable)
{
    _schedulables.push_back(schedulable);
}

void runloop::unschedule(schedulable_ref schedulable)
{
    auto itr = std::find(_schedulables.begin(), _schedulables.end(), schedulable);
    if (itr != _schedulables.end()) {
        _schedulables.erase(itr);
    }
}


#pragma mark - Private Methods

void runloop::_main()
{
    while (_running) {
        for (schedulable_ref schedulable : _schedulables) {
            unsigned time = SDL_GetTicks();
            unsigned last_update = schedulable->_last_update;
            unsigned dtime;
            
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
