/*
 * render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <zge/foundation.h>
#include <zge/matrix.h>
#include <zge/shader_program.h>
#include <zge/texture.h>
#include <zge/uniform.h>
#include <zge/vertex_array.h>
#include <memory>
#include <stack>

ZGE_BEGIN_NAMESPACE

enum ZRenderMatrixType {
    ZRENDER_MATRIX_PROJECTION,
    ZRENDER_MATRIX_MODELVIEW,
    
    // private
    _ZRENDER_MATRIX_COUNT
};

ZGE_FORWARD_DECLARE_SREF(ZLight);

class ZRenderContext : ZNoncopyable, public std::enable_shared_from_this<ZRenderContext> {
public:
    ZRenderContext();
    virtual ~ZRenderContext();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZRenderContext);
    
    virtual void make_current() = 0;
    
    void initialize_shaders();
    
    void push_matrix(ZRenderMatrixType type);
    void push_matrix(ZRenderMatrixType type, const ZMatrix &matrix); // convenience: pushes then multiplies
    void multiply_matrix(ZRenderMatrixType type, const ZMatrix &matrix);
    void load_identity(ZRenderMatrixType type);
    void pop_matrix(ZRenderMatrixType type);
    
    ZShaderProgramRef get_shader_program() const;
    ZMatrix get_matrix(ZRenderMatrixType type) const;
    
    ZRect get_viewport() const;
    void  set_viewport(const ZRect &viewport);
    
    float get_render_scale() const;
    void  set_render_scale(float scale);
    
    void bind_texture(ZTextureRef texture);
    void unbind_texture();
    
    void add_light(ZLightRef light);
    void add_lights(const std::vector<ZLightRef> &lights);
    void remove_lights(const std::vector<ZLightRef> &lights);
    void clear_lights();
    
    void enable_depth_testing();
    void disable_depth_testing();
    
    void clear_buffers();
    
    /* Drawing */
    void draw_array(ZRenderMode mode, ZVertexArrayRef varray, unsigned first_idx, size_t count);
    void draw_elements(ZRenderMode mode, ZVertexArrayRef varray);
    
private:
    void        _initialize_gl();
    void        _update_viewport();
    ZUniformRef _get_matrix_uniform(ZRenderMatrixType type);
    void        _update_matrix_uniforms(ZRenderMatrixType type);
    void        _set_boolean_uniform(const std::string uniform_name, bool flag);
    
    friend ZVertexArray;
    
protected:
    ZRect               _viewport;
    float               _render_scale;
    ZShaderProgramRef   _shader_program;
    bool                _shaders_initialized;
    std::stack<ZMatrix> _matrix_stacks[_ZRENDER_MATRIX_COUNT];
    ZVertexArrayRef     _bound_vertex_array;
    ZTextureRef         _bound_texture;
    std::map<ZLightType, ZLightRef> _lights;
};

ZGE_DEFINE_SREF_TYPE(ZRenderContext);

ZGE_END_NAMESPACE
