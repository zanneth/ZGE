//
//  application.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/application.h"
#include "zge/error.h"
#include "zge/platform.h"
#include "zge/osx_platform.h"
#include "zge/logger.h"
#include "zge/util.h"

#include <iostream>
#include <string>
#include <SDL/SDL.h>

namespace zge {

ZApplication::ZApplication(int argc, char **argv)
{
    setArguments(argc, argv);
}


#pragma mark - Accessors

void ZApplication::setArguments(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i) {
        string str = argv[i];
        _arguments.push_back(str);
    }
}


#pragma mark - Run Loop

ZRunLoop* ZApplication::getMainRunLoop()
{
    if (_mainRunLoop.get() == nullptr) {
        ZRunLoop *runLoop = new ZRunLoop();
        _mainRunLoop.reset(runLoop);
    }
    
    return _mainRunLoop.get();
}

void ZApplication::startMainRunLoop()
{
    ZRunLoop *runLoop = getMainRunLoop();
    runLoop->run();
}


#pragma mark - Running the Application

void runApplication(ZApplication *application)
{
    if (application == NULL) {
        ZError err(kApplicationError, "Application pointer is NULL.");
        util::fatalError(err);
    }
    
    // Initialize SDL engine
    int sdlStat = SDL_Init(SDL_INIT_TIMER  | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (sdlStat < 0) {
        string errorstr = "SDL Failed to initialize: ";
        errorstr += SDL_GetError();
        
        ZError err(kSDLError, errorstr);
        util::fatalError(err);
    }
    
    
    // Initialize the platform interface
    ZPlatform *platform;
#if __APPLE__
    platform = new ZOSXPlatform();
#endif
    
    platform->runApplication(application); // Does not return (OS should start its event loop)
    delete platform;
}

}
