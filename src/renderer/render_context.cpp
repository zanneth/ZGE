/*
 * render_context.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <zge/render_context.h>
#include <zge/fragment_shader.h>
#include <zge/vertex_shader.h>

namespace zge {

ZRenderContext::ZRenderContext(ZDisplayRef display) :
    _gl_context(nullptr),
    _display(display),
    _shaders_loaded(false)
{
    SDL_Window *sdl_window = _display->_get_sdl_window();
    _gl_context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_MakeCurrent(sdl_window, _gl_context);
    
    _shader_program = ZShaderProgramRef(new ZShaderProgram);
    _load_shaders();
    
    for (unsigned i = 0; i < _ZRENDER_MATRIX_COUNT; ++i) {
        _matrix_stacks[i].push(Matrix4f::Identity());
    }
}

ZRenderContext::~ZRenderContext()
{
    if (_gl_context != nullptr) {
        SDL_GL_DeleteContext(_gl_context);
    }
}

#pragma mark - Accessors

ZDisplayRef ZRenderContext::get_display() const { return _display; }

ZShaderProgramRef ZRenderContext::get_shader_program() const { return _shader_program; }

#pragma mark - API

void ZRenderContext::make_current()
{
    SDL_GL_MakeCurrent(_display->_get_sdl_window(), _gl_context);
    _shader_program->use_program();
}

void ZRenderContext::push_matrix(ZRenderMatrixType type)
{
    Matrix4f cur_matrix = _matrix_stacks[type].top();
    _matrix_stacks[type].push(cur_matrix);
}

void ZRenderContext::multiply_matrix(ZRenderMatrixType type, const Matrix4f &matrix)
{
    _matrix_stacks[type].top() *= matrix;
}

void ZRenderContext::load_identity(ZRenderMatrixType type)
{
    _matrix_stacks[type].top() = Matrix4f::Identity();
}

void ZRenderContext::pop_matrix(ZRenderMatrixType type)
{
    _matrix_stacks[type].pop();
}

#pragma mark - Internal

void ZRenderContext::_load_shaders()
{
    if (_shader_program != nullptr && !_shaders_loaded) {
        _shader_program->load_shader_source(ZVertexShaderSource, ZVERTEX_SHADER);
        _shader_program->load_shader_source(ZFragmentShaderSource, ZFRAGMENT_SHADER);
        _shader_program->bind_attribute(ZVERTEX_ATTRIB_POSITION, "position");
        _shader_program->link_program();
    }
}

} // namespace zge
