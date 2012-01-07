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
        std::string str = argv[i];
        _arguments.push_back(str);
    }
}


#pragma mark - Controlling the Main Run Loop

void ZApplication::startMainRunLoop()
{
    if (_mainRunLoop.get() == NULL) {
        LOGGER->log("ERROR: Application's main run loop is not initialized. Could not start run loop.");
    } else {
        _mainRunLoop->run();
    }
}


#pragma mark - Running the Application

void runApplication(ZApplication *application)
{
    if (application == NULL) {
        std::cerr << "FATAL ERROR: Application pointer is NULL." << std::endl;
        std::exit(1);
    }
    
    // Initialize SDL engine
    int sdlStat = SDL_Init(SDL_INIT_TIMER  | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (sdlStat < 0) {
        std::string errorstr = "SDL Failed to initialize: ";
        errorstr += SDL_GetError();
        
        ZError err(ZGE_SDL_ERROR, errorstr);
        zge::util::fatalError(err);
    }
    
    // Create a new run loop for the application
    ZRunLoop *runLoop = new ZRunLoop();
    application->setMainRunLoop(runLoop);
    
    
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
