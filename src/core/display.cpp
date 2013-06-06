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
    SDL_GL_DeleteContext(_gl_context);
    SDL_DestroyWindow(_window);
}

void ZDisplay::initialize()
{
    _init_window();
    _init_opengl();
    _initialized = true;
}

void ZDisplay::update(uint32_t dtime)
{
    SDL_GL_MakeCurrent(_window, _gl_context);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    _last_render += dtime;
    if (_last_render >= _display_mode.refresh_rate * 1000.0) {
        _last_render = 0;
        SDL_GL_SwapWindow(_window);
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
    
    if (_initialized) {
        glViewport(0, 0, _display_mode.width, _display_mode.height);
    }
}

#pragma mark - Internal

void ZDisplay::_init_window()
{
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);     // Request 16-bit depth
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Request double-buffering
    
    _window = SDL_CreateWindow(_display_mode.window_title.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               _display_mode.width,
                               _display_mode.height,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        ZLogger::log_error("Could not create SDL window.");
    }
}

void ZDisplay::_init_opengl()
{
    zassert(_window != nullptr, "Window failed to initialize.");
    
    _gl_context = SDL_GL_CreateContext(_window);
    SDL_GL_MakeCurrent(_window, _gl_context);
    glViewport(0, 0, _display_mode.width, _display_mode.height);
}

} // namespace zge
