//
//  application.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "application.h"

#include <iostream>
#include <string>
#include <SDL/SDL.h>

#include <zge/common/types.h>
#include <zge/system/platform.h>
#include <zge/system/osx/osx_platform.h>
#include <zge/util/logger.h>
#include <zge/util/util.h>

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
        ZError err(ZGE_APPLICATION_ERROR, "Application pointer is NULL.");
        util::fatalError(err);
    }
    
    // Initialize SDL engine
    int sdlStat = SDL_Init(SDL_INIT_TIMER  | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (sdlStat < 0) {
        string errorstr = "SDL Failed to initialize: ";
        errorstr += SDL_GetError();
        
        ZError err(ZGE_SDL_ERROR, errorstr);
        util::fatalError(err);
    }
    
    
    // Initialize the platform interface
    ZPlatform *platform;
#if __APPLE__
    platform = new ZOSXPlatform();
#endif
    
    platform->setApplication(application);
    platform->initialize();    // Does not return (OS should start its event loop)
    
    delete platform;
}

}
