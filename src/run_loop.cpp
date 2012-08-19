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

void ZRunLoop::schedule(ZSchedulableRef ZSchedulable)
{
    _ZSchedulables.push_back(ZSchedulable);
}

void ZRunLoop::unschedule(ZSchedulableRef ZSchedulable)
{
    auto itr = std::find(_ZSchedulables.begin(), _ZSchedulables.end(), ZSchedulable);
    if (itr != _ZSchedulables.end()) {
        _ZSchedulables.erase(itr);
    }
}


#pragma mark - Private Methods

void ZRunLoop::_main()
{
    while (_running) {
        for (ZSchedulableRef ZSchedulable : _ZSchedulables) { 
            unsigned time = SDL_GetTicks();
            unsigned lastUpdate = ZSchedulable->_lastUpdate;
            unsigned dtime;
            
            if (lastUpdate == 0) {
                dtime = 0;
            } else {
                dtime = time - lastUpdate;
            }
            
            ZSchedulable->run(dtime);
            ZSchedulable->_lastUpdate = time;
        }
        
        // very naive timing mechanism.
        SDL_Delay(1);
    }
}

} // namespace zge
