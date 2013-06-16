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
    
    _shader_program->use_program();
    for (unsigned i = 0; i < _ZRENDER_MATRIX_COUNT; ++i) {
        _matrix_stacks[i].push(Matrix4f::Identity());
        _update_uniforms((ZRenderMatrixType)i);
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
    if (_shaders_loaded) {
        _shader_program->use_program();
    }
}

void ZRenderContext::push_matrix(ZRenderMatrixType type, const Matrix4f &matrix)
{
    _matrix_stacks[type].push(matrix);
    _update_uniforms(type);
}

void ZRenderContext::multiply_matrix(ZRenderMatrixType type, const Matrix4f &matrix)
{
    _matrix_stacks[type].top() *= matrix;
    _update_uniforms(type);
}

void ZRenderContext::load_identity(ZRenderMatrixType type)
{
    _matrix_stacks[type].top() = Matrix4f::Identity();
    _update_uniforms(type);
}

void ZRenderContext::pop_matrix(ZRenderMatrixType type)
{
    _matrix_stacks[type].pop();
    _update_uniforms(type);
}

#pragma mark - Internal

void ZRenderContext::_load_shaders()
{
    if (_shader_program != nullptr && !_shaders_loaded) {
        _shader_program->load_shader_source(ZVertexShaderSource, ZVERTEX_SHADER);
        _shader_program->load_shader_source(ZFragmentShaderSource, ZFRAGMENT_SHADER);
        _shader_program->bind_attribute(ZVERTEX_ATTRIB_POSITION, "position");
        _shader_program->link_program();
        
        _shaders_loaded = true;
    }
}

GLint ZRenderContext::_get_matrix_uniform(ZRenderMatrixType type)
{
    static std::string uniform_mapping[_ZRENDER_MATRIX_COUNT] = {
        [ZRENDER_MATRIX_MODELVIEW]  = "modelview",
        [ZRENDER_MATRIX_PROJECTION] = "projection"
    };
    GLint uniform = -1;
    
    if (_shaders_loaded) {
        std::string uniform_name = uniform_mapping[type];
        uniform = _shader_program->get_uniform(uniform_name);
    }
    
    return uniform;
}

void ZRenderContext::_update_uniforms(ZRenderMatrixType type)
{
    GLint uniform = _get_matrix_uniform(type);
    if (uniform != -1) {
        Matrix4f matrix = _matrix_stacks[type].top();
        glUniformMatrix4fv(uniform, 1, GL_FALSE, matrix.data());
        
        std::string matrix_descr = ZGeometry::description(matrix);
        ZLogger::log("Updating matrix type %d for uniform %d with matrix %s", type, uniform, matrix_descr.c_str());
    } else {
        ZLogger::log_error("Could not get uniform for matrix type %d.", type);
    }
}

} // namespace zge
