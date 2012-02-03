//
//  run_loop.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/run_loop.h"

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

void ZRunLoop::schedule(shared_ptr<ZRunnableInterface> runnable)
{
    _runnables.push_back(runnable);
}

void ZRunLoop::unschedule(shared_ptr<ZRunnableInterface> runnable)
{
    for (auto itr = _runnables.begin(); itr != _runnables.end(); ++itr) {
        if (*itr == runnable) {
            _runnables.erase(itr);
            break;
        }
    }
}


#pragma mark - Private Methods

void ZRunLoop::_main()
{
    while (_running) {
        for (auto itr = _runnables.begin(); itr != _runnables.end(); ++itr) {
            unsigned time = SDL_GetTicks();
            unsigned lastUpdate = (*itr)->_lastUpdate;
            unsigned dtime;
            
            if (lastUpdate == 0) {
                dtime = 0;
            } else {
                dtime = time - lastUpdate;
            }
            
            (*itr)->run(dtime);
            (*itr)->_lastUpdate = time;
        }
    }
}

}
