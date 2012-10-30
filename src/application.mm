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
#include <SDL/SDL.h>

namespace zge {

static ZApplication *__current_application = nullptr;

ZApplication::ZApplication(int argc, char **argv) :
    _show_cursor(true),
    _capture_input(false),
    _current_platform(nullptr),
    _time_start(0)
{
    set_arguments(argc, argv);
    _main_runloop._on_main_thread = true;
}

ZApplication::~ZApplication()
{
    if (_current_platform != nullptr) {
        delete _current_platform;
    }
}

#pragma mark - Getting the Application Instance

ZApplication* ZApplication::get_current_application()
{
    return __current_application;
}

#pragma mark - Accessors

void ZApplication::set_arguments(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i) {
        std::string str = argv[i];
        _arguments.push_back(str);
    }
}

#pragma mark - Run Loop

ZRunloop* ZApplication::get_main_runloop()
{
    return &_main_runloop;
}

void ZApplication::start_main_runloop()
{
    _main_runloop.run();
}

#pragma mark - Utility Functions

uint32_t ZApplication::get_time_running()
{
    if (_time_start == 0) {
        return 0;
    }
    
    return SDL_GetTicks() - _time_start;
}

void ZApplication::exit()
{
    _main_runloop.stop();
}

#pragma mark - Handling Events

void ZApplication::handle_application_event(ZApplicationEvent event)
{
    ZLogger::log("Application event received: %x", &event);
    switch (event) {
        case APPLICATION_QUIT_EVENT:
            this->exit();
            break;
        case APPLICATION_ACTIVE_EVENT:
            if (!_show_cursor) {
                SDL_ShowCursor(0);
            }
            if (_capture_input) {
                SDL_WM_GrabInput(SDL_GRAB_ON);
            }
            break;
        case APPLICATION_INACTIVE_EVENT:
            SDL_ShowCursor(1);
            SDL_WM_GrabInput(SDL_GRAB_OFF);
            break;
        default:
            break;
    }
}

#pragma mark - Running the Application

void run_application(ZApplication *application)
{
    if (application == nullptr) {
        ZException expt(APPLICATION_EXCEPTION_CODE);
        expt.extra_info = "Application pointer is NULL.";
        
        throw expt;
    }
    
    if (__current_application != nullptr) {
        delete __current_application;
    }
    __current_application = application;
    
    // initialize SDL engine
    int sdl_stat = SDL_Init(SDL_INIT_TIMER  | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (sdl_stat < 0) {
        std::string errorstr = "SDL Failed to initialize: ";
        errorstr += SDL_GetError();
        
        ZException expt(APPLICATION_EXCEPTION_CODE);
        expt.extra_info = errorstr;
        
        throw expt;
    }
    
    // initialize the RNG
    std::srand(time(NULL));
    
    // initialize the platform interface
    ZPlatform *platform = nullptr;
#if __APPLE__
    platform = new ZOSXPlatform();
#endif
    
    // check if the platform was able to be initialized.
    if (platform == nullptr) {
        ZException expt(APPLICATION_EXCEPTION_CODE);
        expt.extra_info = "Platform not supported.";
        throw expt;
    }
    
    // run the application
    application->_current_platform  = platform;
    application->_time_start = SDL_GetTicks();
    platform->run_application(application); // does not return (should start event loop)
}

} // namespace zge
