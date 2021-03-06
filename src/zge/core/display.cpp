/*
 * display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/core/display.h>
#include <zge/core/engine.h>
#include <zge/util/exception.h>
#include <zge/input/input_manager.h>
#include <zge/util/logger.h>
#include <zge/renderer/opengl.h>
#include <zge/util/util.h>
#include <SDL2/SDL.h>

ZGE_BEGIN_NAMESPACE

struct ZDisplayImpl {
    SDL_Window *window;
    ZResponderRef responder;
};

ZDisplay::ZDisplay(const ZDisplayMode &mode) :
    _impl(new ZDisplayImpl),
    _display_mode(mode),
    _initialized(false),
    _captures_input(false)
{}

ZDisplay::~ZDisplay()
{
    if (_impl->window != nullptr) {
        SDL_DestroyWindow(_impl->window);
    }
}

void ZDisplay::initialize()
{
    if (!_initialized) {
        _init_window();
        _initialized = true;
    }
}

void ZDisplay::update(uint32_t dtime)
{
    swap_buffer();
}

void ZDisplay::resize(int width, int height)
{
    ZDisplayMode mode = _display_mode;
    mode.width = width;
    mode.height = height;
    
    set_display_mode(mode);
}

#pragma mark - Accessors

void ZDisplay::set_display_mode(const ZDisplayMode &mode)
{
    _display_mode = mode;
    
    SDL_SetWindowSize(_impl->window, _display_mode.width, _display_mode.height);
    SDL_SetWindowTitle(_impl->window, _display_mode.window_title.c_str());
    
    // XXX: some way to notify the current render context that the display mode
    // has changed.
}

#pragma mark - API

void ZDisplay::swap_buffer()
{
    SDL_GL_SwapWindow(_impl->window);
}

#pragma mark - Internal

void ZDisplay::_init_window()
{
    uint32_t sdlflags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if (!_display_mode.windowed) {
        sdlflags |= SDL_WINDOW_FULLSCREEN;
    }
    
    // setup some parameters required for using OpenGL with SDL
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);             // request 24-bit depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);            // request double-buffering
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);      // request hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);   // request OpenGL version 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
#if __APPLE__
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
#endif
    
    int width = 0;
    int height = 0;
    if (_display_mode.windowed) {
        width = _display_mode.width;
        height = _display_mode.height;
    } else {
        SDL_DisplayMode sdl_displaymode;
        SDL_GetDesktopDisplayMode(0, &sdl_displaymode);
        width = sdl_displaymode.w;
        height = sdl_displaymode.h;
    }
    
    // create the window
    _impl->window = SDL_CreateWindow(_display_mode.window_title.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               sdlflags);
    if (_impl->window == nullptr) {
        ZLogger::log_error("Could not create SDL window. %s", SDL_GetError());
    }
}

void* ZDisplay::_get_sdl_window()
{
    return static_cast<void *>(_impl->window);
}

ZGE_END_NAMESPACE
