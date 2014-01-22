/*
 * render_context.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <zge/render_context.h>
#include <zge/fragment_shader.h>
#include <zge/logger.h>
#include <zge/vertex_shader.h>
#include <SDL2/SDL.h>

namespace zge {

struct ZRenderContextImpl {
    SDL_GLContext gl_context;
};

ZRenderContext::ZRenderContext(ZDisplayRef display) :
    _display(display),
    _shaders_loaded(false),
    _impl(new ZRenderContextImpl)
{
    SDL_Window *sdl_window = static_cast<SDL_Window *>(_display->_get_sdl_window());
    _impl->gl_context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_MakeCurrent(sdl_window, _impl->gl_context);
    SDL_GL_SetSwapInterval(1); // tell SDL to synchronize the buffer swap with the monitor's refresh rate.
    
    _shader_program = ZShaderProgramRef(new ZShaderProgram);
    _load_shaders();
    
    _shader_program->use_program();
    for (unsigned i = 0; i < _ZRENDER_MATRIX_COUNT; ++i) {
        _matrix_stacks[i].push(ZMatrix::identity());
        _update_matrix_uniforms((ZRenderMatrixType)i);
    }
}

ZRenderContext::~ZRenderContext()
{
    if (_impl->gl_context != nullptr) {
        SDL_GL_DeleteContext(_impl->gl_context);
    }
}

#pragma mark - Accessors

ZDisplayRef ZRenderContext::get_display() const { return _display; }

ZShaderProgramRef ZRenderContext::get_shader_program() const { return _shader_program; }

#pragma mark - API

void ZRenderContext::make_current()
{
    SDL_Window *sdl_window = static_cast<SDL_Window *>(_display->_get_sdl_window());
    SDL_GL_MakeCurrent(sdl_window, _impl->gl_context);
    if (_shaders_loaded) {
        _shader_program->use_program();
    }
}

void ZRenderContext::push_matrix(ZRenderMatrixType type)
{
    ZMatrix top = _matrix_stacks[type].top();
    _matrix_stacks[type].push(top);
}

void ZRenderContext::push_matrix(ZRenderMatrixType type, const ZMatrix &matrix)
{
    push_matrix(type);
    multiply_matrix(type, matrix);
}

void ZRenderContext::multiply_matrix(ZRenderMatrixType type, const ZMatrix &matrix)
{
    _matrix_stacks[type].top() *= matrix;
    _update_matrix_uniforms(type);
}

void ZRenderContext::load_identity(ZRenderMatrixType type)
{
    _matrix_stacks[type].top() = ZMatrix::identity();
    _update_matrix_uniforms(type);
}

void ZRenderContext::pop_matrix(ZRenderMatrixType type)
{
    if (_matrix_stacks[type].size() > 1) {
        _matrix_stacks[type].pop();
        _update_matrix_uniforms(type);
    } else {
        load_identity(type);
    }
}

ZMatrix ZRenderContext::get_matrix(ZRenderMatrixType type) const
{
    return _matrix_stacks[type].top();
}

#pragma mark - Internal

void ZRenderContext::_load_shaders()
{
    if (_shader_program != nullptr && !_shaders_loaded) {
        _shader_program->load_shader_source(ZVertexShaderSource, ZVERTEX_SHADER);
        _shader_program->load_shader_source(ZFragmentShaderSource, ZFRAGMENT_SHADER);
        _shader_program->bind_attribute_index(ZVERTEX_ATTRIB_POSITION, "position");
        _shader_program->bind_attribute_index(ZVERTEX_ATTRIB_COLOR, "color");
        _shader_program->link_program();
        
        _shaders_loaded = true;
    }
}

ZUniformRef ZRenderContext::_get_matrix_uniform(ZRenderMatrixType type)
{
    static std::string uniform_mapping[_ZRENDER_MATRIX_COUNT] = {
        [ZRENDER_MATRIX_MODELVIEW]  = "modelview",
        [ZRENDER_MATRIX_PROJECTION] = "projection"
    };
    ZUniformRef uniform = nullptr;
    
    if (_shaders_loaded) {
        std::string uniform_name = uniform_mapping[type];
        uniform = _shader_program->get_uniform(uniform_name);
    }
    
    return uniform;
}

void ZRenderContext::_update_matrix_uniforms(ZRenderMatrixType type)
{
    ZUniformRef uniform = _get_matrix_uniform(type);
    if (uniform.get()) {
        const ZMatrix &matrix = _matrix_stacks[type].top();
        uniform->set_data(matrix.get_data());
    } else {
        ZLogger::log_error("Could not get uniform for matrix type %d.", type);
    }
}

} // namespace zge
