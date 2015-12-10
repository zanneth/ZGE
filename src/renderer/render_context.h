/*
 * render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <zge/foundation.h>
#include <zge/graphics_buffer.h>
#include <zge/matrix.h>
#include <zge/shader.h>
#include <zge/shader_program.h>
#include <zge/texture.h>
#include <zge/types.h>
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

class ZRenderContext : ZNoncopyable {
public:
    ZRenderContext();
    virtual ~ZRenderContext();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZRenderContext);
    
    /// Set the current render context to this instance.
    virtual void make_current() = 0;
    
    /// Returns the current context for this process.
    static ZRenderContext* get_current_context();
    
    /// Initialize shader program data and compile built-in shaders.
    void initialize_shaders();
    
    // -------------------------------------------------------------------------
    
    /// Push a new matrix on the stack with the specified type.
    void push_matrix(ZRenderMatrixType type);
    
    /// Push a new matrix on the stack and multiply the top.
    void push_matrix(ZRenderMatrixType type, const ZMatrix &matrix);
    
    /// Multiply the current top matrix.
    void multiply_matrix(ZRenderMatrixType type, const ZMatrix &matrix);
    
    /// Load the identity matrix into the stack's top matrix.
    void load_identity(ZRenderMatrixType type);
    
    /// Pop the matrix stack.
    void pop_matrix(ZRenderMatrixType type);
    
    /// Returns the current matrix for the specified type.
    ZMatrix get_matrix(ZRenderMatrixType type) const;
    
    // -------------------------------------------------------------------------
    
    /// Returns the shader program associated with this context.
    ZShaderProgramRef get_shader_program() const;
    
    /// Allocates a new vertex array.
    ZVertexArrayRef create_vertex_array();
    
    /// Allocates a new graphics buffer.
    ZGraphicsBufferRef create_graphics_buffer(ZBufferTarget target = ZBUFFER_TARGET_ARRAY);
    
    /// Allocates a new elements buffer.
    ZElementGraphicsBufferRef create_elements_buffer();
    
    /// Allocates a shader program.
    ZShaderProgramRef create_shader_program();
    
    /// Allocates a shader.
    ZShaderRef create_shader(ZShaderType type);
    
    /// Allocates a texture object.
    ZTextureRef create_texture(ZImageRef image);
    
    /// Allocates a texture object, reading image data from disk first.
    ZTextureRef create_texture(const std::string &path);
    
    // -------------------------------------------------------------------------
    
    /// Returns the viewport used during rendering.
    ZRect get_viewport() const;
    
    /// Set the viewport to use during rendering.
    void set_viewport(const ZRect &viewport);
    
    /// Returns the pixel scale (density) used during final rendering.
    float get_render_scale() const;
    
    /// Sets the pixel scale (density) used during final rendering.
    void set_render_scale(float scale);
    
    /// Returns true if depth testing is enabled during rendering.
    bool depth_testing_is_enabled() const;
    
    /// Set whether depth testing should be enabled during rendering.
    void set_depth_testing_enabled(bool enabled);
    
    // -------------------------------------------------------------------------
    
    /// Bind a texture to this context.
    void bind_texture(ZTextureRef texture);
    
    /// Unbind the current texture from this context.
    void unbind_texture();
    
    /// Bind a vertex array to this context.
    void bind_vertex_array(ZVertexArrayRef varray);
    
    /// Unbind the current vertex array from this context.
    void unbind_vertex_array();
    
    // -------------------------------------------------------------------------
    
    /// Add a light to this context to use during rendering.
    void add_light(ZLightRef light);
    
    /// Add multiple lights to the context.
    void add_lights(const std::vector<ZLightRef> &lights);
    
    /// Remove lights from this context.
    void remove_lights(const std::vector<ZLightRef> &lights);
    
    /// Remove all lights from the rendering context.
    void clear_lights();
    
    // -------------------------------------------------------------------------
    
    /// Prepares the context for rendering.
    void prepare_render();
    
    /// Draw elements using a vertex array.
    void draw_array(ZRenderMode mode, ZVertexArrayRef varray, unsigned first_idx, size_t count);
    
    /// Draw elements using a vertex array with an elements buffer.
    void draw_elements(ZRenderMode mode, ZVertexArrayRef varray);
    
private:
    void        _initialize_gl();
    void        _clear_buffers();
    void        _update_viewport();
    ZUniformRef _get_matrix_uniform(ZRenderMatrixType type);
    void        _update_matrix_uniforms(ZRenderMatrixType type);
    void        _set_boolean_uniform(const std::string uniform_name, bool flag);
    void        _setup_vertex_attrib_ptr(ZGraphicsBufferRef buffer, ZVertexAttributeIndex index);
    void        _use_shader_program(ZShaderProgramRef program);
    void        _update_dirty_uniforms();
    void        _update_uniform_data(ZUniformRef uniform);
    
protected:
    ZRect               _viewport;
    float               _render_scale;
    ZShaderProgramRef   _shader_program;
    bool                _shaders_initialized;
    bool                _depth_testing_enabled;
    std::stack<ZMatrix> _matrix_stacks[_ZRENDER_MATRIX_COUNT];
    ZVertexArrayRef     _bound_vertex_array;
    ZTextureRef         _bound_texture;
    std::map<ZLightType, ZLightRef> _lights;
    
    static ZRenderContext *__current_context;
};

ZGE_DEFINE_SREF_TYPE(ZRenderContext);

ZGE_END_NAMESPACE
