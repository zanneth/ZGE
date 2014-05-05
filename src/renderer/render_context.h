/*
 * render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <memory>
#include <stack>
#include <zge/defines.h>
#include <zge/display.h>
#include <zge/matrix.h>
#include <zge/noncopyable.h>
#include <zge/shader_program.h>
#include <zge/uniform.h>
#include <zge/vertex_array.h>

BEGIN_ZGE_NAMESPACE

enum ZRenderMatrixType {
    ZRENDER_MATRIX_PROJECTION,
    ZRENDER_MATRIX_MODELVIEW,
    
    // private
    _ZRENDER_MATRIX_COUNT
};

typedef std::shared_ptr<class ZRenderContext> ZRenderContextRef;

class ZRenderContext : ZNoncopyable, public std::enable_shared_from_this<ZRenderContext> {
    ZDisplayRef          _display;
    ZShaderProgramRef    _shader_program;
    bool                 _shaders_loaded;
    std::stack<ZMatrix>  _matrix_stacks[_ZRENDER_MATRIX_COUNT];
    ZVertexArrayRef      _bound_vertex_array;
    
    std::auto_ptr<struct ZRenderContextImpl> _impl;
    
public:
    ZRenderContext(ZDisplayRef display);
    virtual ~ZRenderContext();
    
    ZDisplayRef       get_display() const;
    ZShaderProgramRef get_shader_program() const;
    
    void make_current();
    static ZRenderContextRef get_current_context();
    
    void push_matrix(ZRenderMatrixType type);
    void push_matrix(ZRenderMatrixType type, const ZMatrix &matrix); // convenience: pushes then multiplies
    void multiply_matrix(ZRenderMatrixType type, const ZMatrix &matrix);
    void load_identity(ZRenderMatrixType type);
    void pop_matrix(ZRenderMatrixType type);
    
    ZMatrix get_matrix(ZRenderMatrixType type) const;
    
    /* Drawing */
    void draw_array(ZRenderMode mode, ZVertexArrayRef varray, unsigned first_idx, size_t count);
    void draw_elements(ZRenderMode mode, ZVertexArrayRef varray);
    
private:
    void        _load_shaders();
    ZUniformRef _get_matrix_uniform(ZRenderMatrixType type);
    void        _update_matrix_uniforms(ZRenderMatrixType type);
    
    friend ZVertexArray;
};

END_ZGE_NAMESPACE
