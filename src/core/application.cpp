/*
 * application.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#include <zge/application.h>
#include <zge/exception.h>
#include <zge/logger.h>
#include <zge/run_loop.h>
#include <zge/util.h>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>

ZGE_BEGIN_NAMESPACE

static ZApplication *__current_application = nullptr;

ZApplication::ZApplication(int argc, const char **argv) :
    _show_cursor(true)
{
    set_arguments(argc, argv);
    _main_runloop._on_main_thread = true;
}

ZApplication::~ZApplication()
{}

#pragma mark - Getting the Application Instance

ZApplication* ZApplication::get_current_application()
{
    return __current_application;
}

#pragma mark - Running

void ZApplication::run()
{
    if (__current_application != nullptr) {
        delete __current_application;
    }
    __current_application = this;
        
    // initialize SDL
    int sdl_result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (sdl_result < 0) {
        ZException ex(ZAPPLICATION_EXCEPTION_CODE);
        ex.extra_info = ZUtil::format("SDL failed to initialize: %s", SDL_GetError());
        throw ex;
    }
    
    // initialize random number generator
    std::srand((unsigned)std::time(NULL));
    
    // perform any remaining initializations
    _time_start = ZUtil::get_current_time();
    
    // callback to client to notify application is ready to run
    application_ready();
    
    // start main run loop (doesn't return)
    start_main_runloop();
}

#pragma mark - Accessors

std::vector<std::string> ZApplication::get_arguments() { return _arguments; }

void ZApplication::set_arguments(int argc, const char **argv)
{
    for (int i = 0; i < argc; ++i) {
        std::string str = argv[i];
        _arguments.push_back(str);
    }
}

bool ZApplication::shows_cursor() const { return _show_cursor; }

void ZApplication::set_shows_cursor(bool cursor) { _show_cursor = cursor; }

bool ZApplication::get_use_relative_cursor() const { return _use_relative_cursor; }

void ZApplication::set_use_relative_cursor(bool use_relative)
{
    SDL_SetRelativeMouseMode((use_relative ? SDL_TRUE : SDL_FALSE));
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

ZTimeInterval ZApplication::get_time_running()
{
    return ZUtil::get_current_time() - _time_start;
}

void ZApplication::exit()
{
    _main_runloop.stop();
}

#pragma mark - Handling Events

void ZApplication::handle_application_event(const ZEvent &event)
{
    ZApplicationEvent app_event = event.application_event;
    switch (app_event) {
        case ZAPPLICATION_QUIT_EVENT:
            this->exit();
            break;
        case ZAPPLICATION_ACTIVE_EVENT:
            if (!_show_cursor) {
                SDL_ShowCursor(0);
            }
            break;
        case ZAPPLICATION_INACTIVE_EVENT:
            SDL_ShowCursor(1);
            break;
        default:
            break;
    }
}

ZGE_END_NAMESPACE
