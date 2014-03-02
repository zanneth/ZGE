/*
 * render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <memory>
#include <stack>
#include <zge/display.h>
#include <zge/matrix.h>
#include <zge/noncopyable.h>
#include <zge/shader_program.h>
#include <zge/uniform.h>
#include <zge/vertexarray.h>

BEGIN_ZGE_NAMESPACE

enum ZRenderMatrixType {
    ZRENDER_MATRIX_PROJECTION,
    ZRENDER_MATRIX_MODELVIEW,
    
    // private
    _ZRENDER_MATRIX_COUNT
};

class ZRenderContext : ZNoncopyable {
    ZDisplayRef          _display;
    ZShaderProgramRef    _shader_program;
    bool                 _shaders_loaded;
    std::stack<ZMatrix>  _matrix_stacks[_ZRENDER_MATRIX_COUNT];
    ZVertexArrayRef      _bound_vertex_array;
    
    std::auto_ptr<struct ZRenderContextImpl> _impl;
    
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
    void push_matrix(ZRenderMatrixType type, const ZMatrix &matrix); // convenience: pushes then multiplies
    void multiply_matrix(ZRenderMatrixType type, const ZMatrix &matrix);
    void load_identity(ZRenderMatrixType type);
    void pop_matrix(ZRenderMatrixType type);
    
    ZMatrix get_matrix(ZRenderMatrixType type) const;
    
    /* Drawing */
    void draw_elements(ZRenderMode mode, ZComponentType element_type, ZVertexArrayRef varray, size_t count);
    
protected:
    void        _load_shaders();
    ZUniformRef _get_matrix_uniform(ZRenderMatrixType type);
    void        _update_matrix_uniforms(ZRenderMatrixType type);
    void        _bind_vertex_array(ZVertexArrayRef varray);
    void        _unbind_vertex_array();
};

typedef std::shared_ptr<ZRenderContext> ZRenderContextRef;

END_ZGE_NAMESPACE
