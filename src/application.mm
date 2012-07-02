/*
 * application.mm
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#include "zge/application.h"
#include "zge/exception.h"
#include "zge/platform.h"
#include "zge/osx_platform.h"
#include "zge/logger.h"
#include "zge/run_loop.h"
#include "zge/util.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <SDL/SDL.h>

namespace zge {

static ZRunLoop *_mainRunLoop = nullptr;

ZApplication::ZApplication(int argc, char **argv) :
    _currentPlatform(nullptr),
    _timeBeganRunning(0)
{
    setArguments(argc, argv);
}

ZApplication::~ZApplication()
{
    if (_mainRunLoop != nullptr) {
        _mainRunLoop->stop();
        delete _mainRunLoop;
    }
    
    if (_currentPlatform != nullptr) {
        delete _currentPlatform;
    }
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
        _mainRunLoop->_onMainThread = true;
    }
    
    return _mainRunLoop;
}

void ZApplication::startMainRunLoop()
{
    ZRunLoop *runLoop = getMainRunLoop();
    runLoop->run();
}


#pragma mark - Utility Functions

unsigned ZApplication::getSecondsRunning()
{
    if (_timeBeganRunning == 0) {
        return 0;
    }
    
    return SDL_GetTicks() - _timeBeganRunning;
}


#pragma mark - Running the Application

void runApplication(ZApplication *application)
{
    if (application == NULL) {
        ZApplicationException expt;
        expt.extraInfo = "Application pointer is NULL.";
        
        throw expt;
    }
    
    // Initialize SDL engine
    int sdlStat = SDL_Init(SDL_INIT_TIMER  | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (sdlStat < 0) {
        std::string errorstr = "SDL Failed to initialize: ";
        errorstr += SDL_GetError();
        
        ZApplicationException expt;
        expt.extraInfo = errorstr;
        
        throw expt;
    }
    
    // Initialize the RNG
    std::srand(time(NULL));
    
    // Initialize the platform interface
    ZPlatform *platform = nullptr;
#if __APPLE__
    platform = new ZOSXPlatform();
#endif
    
    // Check if the platform was able to be initialized.
    if (platform == nullptr) {
        ZApplicationException expt;
        expt.extraInfo = "Platform not supported.";
        throw expt;
    }
    
    // Run the application
    application->_currentPlatform  = platform;
    application->_timeBeganRunning = SDL_GetTicks();
    platform->runApplication(application); // Does not return (should start event loop)
}

} // namespace zge
