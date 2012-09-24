/*
 * gl_display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/gl_display.h"
#include "zge/exception.h"
#include "zge/gl_includes.h"
#include "zge/logger.h"
#include "zge/matrix.h"
#include "zge/util.h"
#include "zge/vector.h"

#include <iostream>
#include <string>

namespace zge {

gldisplay::gldisplay() : display(),
    _surface(nullptr) {}

gldisplay::gldisplay(const display_mode &mode) : display(mode),
    _surface(nullptr) {}

gldisplay::~gldisplay()
{
    if (_surface != nullptr) {
        SDL_FreeSurface(_surface);
    }
}


#pragma mark - Initialization

void gldisplay::initialize()
{
    if (!_is_initialized) {
        _load_surface();
        _change_window_title(_display_mode.window_title);
        _init_opengl();
        
        _is_initialized = true;
    } else {
        logger::warn("Display already initialized.");
    }
}


#pragma mark - Rendering

void gldisplay::render(unsigned dtime)
{    
    _last_render += dtime;
    if (_last_render >= _display_mode.refresh_rate * 1000.0) {
        _last_render = 0;
        SDL_GL_SwapBuffers();
    }
}


#pragma mark - Changing Properties

void gldisplay::set_display_mode(const display_mode &mode)
{
    if (mode.window_title != _display_mode.window_title) {
        _change_window_title(mode.window_title);
    }
    
    _display_mode = mode;
}


#pragma mark - Private Methods

void gldisplay::_load_surface()
{
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);     // Request 16-bit depth
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Request double-buffering
    
    Uint32 sdl_flags = SDL_OPENGL;
    if (!_display_mode.windowed) {
        sdl_flags |= SDL_FULLSCREEN;
    }
    
    if (_surface != NULL) {
        SDL_FreeSurface(_surface);
    }
    
    _surface = SDL_SetVideoMode(_display_mode.width, _display_mode.height, 0, sdl_flags);
    if (!_surface) {
        std::string errorstr = "The OpenGL display surface failed to initialize: ";
        errorstr += SDL_GetError();
        
        display_exception expt;
        expt.extra_info = errorstr;
        throw expt;
    }
}

void gldisplay::_init_opengl()
{
    glEnable(GL_DEPTH_TEST);
}

void gldisplay::_change_window_title(std::string new_title)
{
    const char *window_title = new_title.c_str();
    SDL_WM_SetCaption(window_title, window_title);
}

} // namespace zge
