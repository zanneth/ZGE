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


#pragma mark - Managing Runnables in the Run Loop

void ZRunLoop::schedule(ZRunnableInterfaceRef runnable)
{
    _runnables.push_back(runnable);
}

void ZRunLoop::unschedule(ZRunnableInterfaceRef runnable)
{
    auto itr = std::find(_runnables.begin(), _runnables.end(), runnable);
    if (itr != _runnables.end()) {
        _runnables.erase(itr);
    }
}


#pragma mark - Private Methods

void ZRunLoop::_main()
{
    while (_running) {
        for (ZRunnableInterfaceRef runnable : _runnables) { 
            unsigned time = SDL_GetTicks();
            unsigned lastUpdate = runnable->_lastUpdate;
            unsigned dtime;
            
            if (lastUpdate == 0) {
                dtime = 0;
            } else {
                dtime = time - lastUpdate;
            }
            
            runnable->run(dtime);
            runnable->_lastUpdate = time;
        }
    }
}

} // namespace zge
