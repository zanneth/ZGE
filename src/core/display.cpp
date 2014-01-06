/*
 * display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/display.h>
#include <zge/engine.h>
#include <zge/exception.h>
#include <zge/input_manager.h>
#include <zge/logger.h>
#include <zge/opengl.h>
#include <zge/util.h>
#include <SDL2/SDL.h>

namespace zge {

struct ZDisplayImpl {
    SDL_Window *window;
    ZResponderRef responder;
};

ZDisplay::ZDisplay(const ZDisplayMode &mode) :
    _impl(new ZDisplayImpl),
    _display_mode(mode)
{}

ZDisplay::~ZDisplay()
{
    ZInputManagerRef input_manager = ZEngine::instance()->get_input_manager();
    input_manager->remove_responder(_impl->responder);
    if (_impl->window != nullptr) {
        SDL_DestroyWindow(_impl->window);
    }
}

void ZDisplay::initialize()
{
    _init_window();
    
    ZInputManagerRef input_manager = ZEngine::instance()->get_input_manager();
    SDL_Window *window = _impl->window;
    std::weak_ptr<ZDisplay> weak_display = shared_from_this();
    _impl->responder = input_manager->add_responder([window, weak_display](const ZEvent &event) {
        if (event.type == ZAPPLICATION_EVENT) {
            ZDisplayRef strong_display = weak_display.lock();
            if (strong_display.get()) {
                bool grab = (event.application_event != ZAPPLICATION_INACTIVE_EVENT && strong_display->captures_input());
                SDL_SetWindowGrab(window, (grab ? SDL_TRUE : SDL_FALSE));
            }
        }
    });
    
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
    
    SDL_SetWindowSize(_impl->window, _display_mode.width, _display_mode.height);
    SDL_SetWindowTitle(_impl->window, _display_mode.window_title.c_str());
    glViewport(0, 0, _display_mode.width, _display_mode.height);
}

void ZDisplay::set_captures_input(bool capture)
{
    _captures_input = capture;
    if (_impl->window != nullptr) {
        SDL_SetWindowGrab(_impl->window, (capture ? SDL_TRUE : SDL_FALSE));
    }
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
    
    // create the window
    _impl->window = SDL_CreateWindow(_display_mode.window_title.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               _display_mode.width,
                               _display_mode.height,
                               sdlflags);
    if (_impl->window == nullptr) {
        ZLogger::log_error("Could not create SDL window.");
    }
}

void* ZDisplay::_get_sdl_window()
{
    return static_cast<void *>(_impl->window);
}

} // namespace zge
