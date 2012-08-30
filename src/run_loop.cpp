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

ZRunLoop::ZRunLoop() :
    _running(false) {}

ZRunLoop::~ZRunLoop()
{
    _running = false;
}


#pragma mark - Starting the Run Loop

void ZRunLoop::run()
{
    _running = true;
    _main();
}

void ZRunLoop::stop()
{
    _running = false;
}


#pragma mark - Managing ZSchedulables in the Run Loop

void ZRunLoop::schedule(ZSchedulableRef schedulable)
{
    _schedulables.push_back(schedulable);
}

void ZRunLoop::unschedule(ZSchedulableRef schedulable)
{
    auto itr = std::find(_schedulables.begin(), _schedulables.end(), schedulable);
    if (itr != _schedulables.end()) {
        _schedulables.erase(itr);
    }
}


#pragma mark - Private Methods

void ZRunLoop::_main()
{
    while (_running) {
        for (ZSchedulableRef schedulable : _schedulables) {
            unsigned time = SDL_GetTicks();
            unsigned lastUpdate = schedulable->_lastUpdate;
            unsigned dtime;
            
            if (lastUpdate == 0) {
                dtime = 0;
            } else {
                dtime = time - lastUpdate;
            }
            
            schedulable->run(dtime);
            schedulable->_lastUpdate = time;
        }
        
        // very naive timing mechanism.
        SDL_Delay(1);
    }
}

} // namespace zge
