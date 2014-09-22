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
#include <zge/texture.h>
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
typedef std::shared_ptr<class ZLight> ZLightRef;

class ZRenderContext : ZNoncopyable, public std::enable_shared_from_this<ZRenderContext> {
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
    
    void bind_texture(ZTextureRef texture);
    void unbind_texture();
    
    void add_light(ZLightRef light);
    void add_lights(const std::vector<ZLightRef> &lights);
    void remove_lights(const std::vector<ZLightRef> &lights);
    void clear_lights();
    
    void enable_depth_testing();
    void disable_depth_testing();
    
    /* Drawing */
    void draw_array(ZRenderMode mode, ZVertexArrayRef varray, unsigned first_idx, size_t count);
    void draw_elements(ZRenderMode mode, ZVertexArrayRef varray);
    
private:
    void        _load_shaders();
    ZUniformRef _get_matrix_uniform(ZRenderMatrixType type);
    void        _update_matrix_uniforms(ZRenderMatrixType type);
    void        _set_boolean_uniform(const std::string uniform_name, bool flag);
    
    friend ZVertexArray;
    
private:
    std::unique_ptr<struct ZRenderContextImpl> _impl;
};

END_ZGE_NAMESPACE
