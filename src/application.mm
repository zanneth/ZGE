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

static runloop *_main_runloop = nullptr;

application::application(int argc, char **argv) :
    _current_platform(nullptr),
    _time_start(0)
{
    set_arguments(argc, argv);
}

application::~application()
{
    if (_main_runloop != nullptr) {
        _main_runloop->stop();
        delete _main_runloop;
    }
    
    if (_current_platform != nullptr) {
        delete _current_platform;
    }
}


#pragma mark - Accessors

void application::set_arguments(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i) {
        std::string str = argv[i];
        _arguments.push_back(str);
    }
}


#pragma mark - Run Loop

runloop* application::get_main_runloop()
{
    if (_main_runloop == nullptr) {
        _main_runloop = new runloop();
        _main_runloop->_on_main_thread = true;
    }
    
    return _main_runloop;
}

void application::start_main_runloop()
{
    runloop *loop = get_main_runloop();
    loop->run();
}


#pragma mark - Utility Functions

unsigned application::get_secs_running()
{
    if (_time_start == 0) {
        return 0;
    }
    
    return SDL_GetTicks() - _time_start;
}


#pragma mark - Running the Application

void run_application(application *application)
{
    if (application == nullptr) {
        application_exception expt;
        expt.extra_info = "Application pointer is NULL.";
        
        throw expt;
    }
    
    // initialize SDL engine
    int sdl_stat = SDL_Init(SDL_INIT_TIMER  | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (sdl_stat < 0) {
        std::string errorstr = "SDL Failed to initialize: ";
        errorstr += SDL_GetError();
        
        application_exception expt;
        expt.extra_info = errorstr;
        
        throw expt;
    }
    
    // initialize the RNG
    std::srand(time(NULL));
    
    // initialize the platform interface
    platform *platform = nullptr;
#if __APPLE__
    platform = new osx_platform();
#endif
    
    // check if the platform was able to be initialized.
    if (platform == nullptr) {
        application_exception expt;
        expt.extra_info = "Platform not supported.";
        throw expt;
    }
    
    // run the application
    application->_current_platform  = platform;
    application->_time_start = SDL_GetTicks();
    platform->run_application(application); // does not return (should start event loop)
}

} // namespace zge
