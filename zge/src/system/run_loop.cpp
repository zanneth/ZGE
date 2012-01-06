//
//  run_loop.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/5/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "run_loop.h"

#include <iostream>
#include <SDL/SDL.h>

#include <zge/interfaces/runnable_interface.h>


namespace zge {

ZRunLoop::ZRunLoop() :
    _running(false)
{}

ZRunLoop::~ZRunLoop()
{
    _running = false;
}


#pragma mark - Starting the Run Loop

void ZRunLoop::run()
{
    _running = true;
    _startRunLoop();
}


#pragma mark - Managing Runnables in the Run Loop

void ZRunLoop::schedule(boost::shared_ptr<ZRunnableInterface> runnable)
{
    _runnables.push_back(runnable);
}

void ZRunLoop::unschedule(boost::shared_ptr<ZRunnableInterface> runnable)
{
    RunnableIterator itr;
    for (itr = _runnables.begin(); itr != _runnables.end(); ++itr) {
        if (*itr == runnable) {
            _runnables.erase(itr);
            break;
        }
    }
}


#pragma mark - Private Methods

void ZRunLoop::_startRunLoop()
{
    while (_running) {
        RunnableIterator itr;
        for (itr = _runnables.begin(); itr != _runnables.end(); ++itr) {
            unsigned time = SDL_GetTicks();
            unsigned lastUpdate = (*itr)->_lastUpdate;
            unsigned dtime;
            
            if (lastUpdate == 0) {
                dtime = 0;
            } else {
                dtime = time - lastUpdate;
            }
            
            (*itr)->update(dtime);
            (*itr)->_lastUpdate = time;
        }
    }
}

}
