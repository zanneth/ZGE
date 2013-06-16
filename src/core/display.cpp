/*
 * display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/display.h>
#include <zge/exception.h>
#include <zge/logger.h>
#include <zge/util.h>
#include <SDL2/SDL_opengl.h>

namespace zge {

ZDisplay::ZDisplay(const ZDisplayMode &mode) :
    _display_mode(mode)
{}

ZDisplay::~ZDisplay()
{
    SDL_DestroyWindow(_window);
}

void ZDisplay::initialize()
{
    _init_window();
    _initialized = true;
}

void ZDisplay::update(uint32_t dtime)
{
    _last_render += dtime;
    if (_last_render >= _display_mode.refresh_rate * 1000.0) {
        _last_render = 0;
        swap_buffer();
    }
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
    
    SDL_SetWindowSize(_window, _display_mode.width, _display_mode.height);
    SDL_SetWindowTitle(_window, _display_mode.window_title.c_str());
}

#pragma mark - API

void ZDisplay::swap_buffer()
{
    SDL_GL_SwapWindow(_window);
}

#pragma mark - Internal

void ZDisplay::_init_window()
{
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);     // Request 16-bit depth
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Request double-buffering
    
    uint32_t sdlflags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    if (!_display_mode.windowed) {
        sdlflags |= SDL_WINDOW_FULLSCREEN;
    }
    _window = SDL_CreateWindow(_display_mode.window_title.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               _display_mode.width,
                               _display_mode.height,
                               sdlflags);
    if (_window == nullptr) {
        ZLogger::log_error("Could not create SDL window.");
    }
}

SDL_Window* ZDisplay::_get_sdl_window()
{
    return _window;
}

} // namespace zge
