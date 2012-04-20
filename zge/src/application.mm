/*
 * application.mm
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
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

static ZRunLoop *_mainRunLoop = nullptr;

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


#pragma mark - Run Loop

ZRunLoop* ZApplication::getMainRunLoop()
{
    if (_mainRunLoop == nullptr) {
        _mainRunLoop = new ZRunLoop();
    }
    
    return _mainRunLoop;
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
        ZApplicationException expt;
        expt.description = "Application pointer is NULL.";
        
        throw expt;
    }
    
    // Initialize SDL engine
    int sdlStat = SDL_Init(SDL_INIT_TIMER  | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (sdlStat < 0) {
        std::string errorstr = "SDL Failed to initialize: ";
        errorstr += SDL_GetError();
        
        ZApplicationException expt;
        expt.description = errorstr;
        
        throw expt;
    }
    
    
    // Initialize the platform interface
    ZPlatform *platform;
#if __APPLE__
    platform = new ZOSXPlatform();
#endif
    
    platform->runApplication(application); // Does not return (OS should start its event loop)
    delete platform;
}

} // namespace zge
