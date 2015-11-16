/*
 * display_render_context.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/06/2015
 */

#include <zge/display_render_context.h>
#include <zge/display.h>
#include <SDL2/SDL.h>

ZGE_BEGIN_NAMESPACE

struct ZDisplayRenderContextImpl {
    SDL_GLContext gl_context;
    ZDisplayRef display;
};

ZDisplayRenderContext::ZDisplayRenderContext(ZDisplayRef display) :
    _impl(new ZDisplayRenderContextImpl)
{
    _impl->display = display;
    
    // setup backing context
    SDL_Window *sdl_window = static_cast<SDL_Window *>(_impl->display->_get_sdl_window());
    _impl->gl_context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_MakeCurrent(sdl_window, _impl->gl_context);
    SDL_GL_SetSwapInterval(1); // tell SDL to synchronize the buffer swap with the monitor's refresh rate.
    
    // setup viewport
    ZDisplayMode display_mode = _impl->display->get_display_mode();
    ZRect viewport = ZRect{0.0, 0.0, float(display_mode.width), float(display_mode.height)};
    set_viewport(viewport);
    set_render_scale(display_mode.scale);
    
    // initialize shaders
    initialize_shaders();
}

ZDisplayRenderContext::~ZDisplayRenderContext()
{
    if (_impl->gl_context != nullptr) {
        SDL_Window *sdl_window = static_cast<SDL_Window *>(_impl->display->_get_sdl_window());
        SDL_GL_MakeCurrent(sdl_window, nullptr);
        SDL_GL_DeleteContext(_impl->gl_context);
    }
}

#pragma mark - Accessors

ZDisplayRef ZDisplayRenderContext::get_display() const { return _impl->display; }

#pragma mark - ZRenderContext Overrides

void ZDisplayRenderContext::make_current()
{
    SDL_Window *sdl_window = static_cast<SDL_Window *>(_impl->display->_get_sdl_window());
    SDL_GL_MakeCurrent(sdl_window, _impl->gl_context);
    __current_context = this;
}

ZGE_END_NAMESPACE
