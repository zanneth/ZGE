/*
 * render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <stack>
#include <zge/display.h>
#include <zge/geometry.h>
#include <zge/noncopyable.h>
#include <zge/shader_program.h>

namespace zge {

enum ZRenderMatrixType {
    ZRENDER_MATRIX_PROJECTION,
    ZRENDER_MATRIX_MODELVIEW,
    
    // private
    _ZRENDER_MATRIX_COUNT
};

class ZRenderContext : ZNoncopyable {
    SDL_GLContext        _gl_context;
    ZDisplayRef          _display;
    ZShaderProgramRef    _shader_program;
    bool                 _shaders_loaded;
    std::stack<Matrix4f> _matrix_stacks[_ZRENDER_MATRIX_COUNT];
    
public:
    ZRenderContext(ZDisplayRef display);
    virtual ~ZRenderContext();
    
    /* Accessors */
    ZDisplayRef       get_display() const;
    ZShaderProgramRef get_shader_program() const;
    
    /* Setting the Current Context */
    void make_current();
    
    /* Managing Matrices */
    void push_matrix(ZRenderMatrixType type);
    void multiply_matrix(ZRenderMatrixType type, const Matrix4f &matrix);
    void load_identity(ZRenderMatrixType type);
    void pop_matrix(ZRenderMatrixType type);
    
protected:
    void _load_shaders();
};

typedef std::shared_ptr<ZRenderContext> ZRenderContextRef;

} // namespace zge
