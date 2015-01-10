/*
 * display_render_context.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/06/2015
 */

#include <zge/display_render_context.h>
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
    
    SDL_Window *sdl_window = static_cast<SDL_Window *>(_impl->display->_get_sdl_window());
    _impl->gl_context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_MakeCurrent(sdl_window, _impl->gl_context);
    SDL_GL_SetSwapInterval(1); // tell SDL to synchronize the buffer swap with the monitor's refresh rate.
    
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
    
    ZShaderProgramRef shader_program = get_shader_program();
    if (shader_program) {
        shader_program->use_program();
    }
}

ZGE_END_NAMESPACE

