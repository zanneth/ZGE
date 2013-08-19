/*
 * gl_buffer.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */
 
#pragma once

#include <zge/noncopyable.h>
#include <zge/opengl.h>
#include <zge/types.h>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <vector>

#define ZUNALLOCATED_BUFFER 0
#define ZUNBOUND_TARGET     0

namespace zge {

enum ZBufferComponentType {
    ZBUFFER_COMPONENT_TYPE_UNKNOWN = 0,
    ZBUFFER_COMPONENT_TYPE_BYTE = GL_BYTE,
    ZBUFFER_COMPONENT_TYPE_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    ZBUFFER_COMPONENT_TYPE_SHORT = GL_SHORT,
    ZBUFFER_COMPONENT_TYPE_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    ZBUFFER_COMPONENT_TYPE_INT = GL_INT,
    ZBUFFER_COMPONENT_TYPE_UNSIGNED_INT = GL_UNSIGNED_INT,
    ZBUFFER_COMPONENT_TYPE_FLOAT = GL_FLOAT,
    ZBUFFER_COMPONENT_TYPE_DOUBLE = GL_DOUBLE
};

struct ZBufferAttribute {
    ZVertexAttributeIndex   index;                  // generic vertex attribute index
    unsigned                components_per_vertex;  // components per vertex attribute (1, 2, 3, or 4)
    ZBufferComponentType    component_type;         // data type of each component
    bool                    normalized;             // whether fixed-point data values should be normalized
    size_t                  stride;                 // byte offset between consecutive vertex attributes
    uintptr_t               offset;                 // offset of the first component of the first vertex attribute
};

class ZGLVertexArray;

class ZGLBuffer : ZNoncopyable {
    GLuint _buffer;
    GLenum _target;
    std::vector<ZBufferAttribute> _attributes;
    ZGLVertexArray *_vertex_array; // weak

public:
    ZGLBuffer();
    ZGLBuffer(ZGLBuffer&&);
    ~ZGLBuffer();
    
    ZGLBuffer& operator=(ZGLBuffer&&);
    
    /* Accessors */
    GLuint  get_buffer() { return _buffer; }
    GLenum  get_target() { return _target; }
    void    set_target(GLenum target) { _target = target; }
    
    /* Attributes */
    void             add_attribute(ZBufferAttribute attribute);
    ZBufferAttribute get_attribute(ZVertexAttributeIndex index);
    std::vector<ZBufferAttribute> get_attributes() { return _attributes; }
    void             clear_attributes();
    
    /* Loading Data */
    void load_data(GLsizeiptr size, const GLvoid *data, GLenum usage);
    void load_subdata(GLsizeiptr offset, GLsizeiptr size, const GLvoid *data);
    
    /* Actions */
    void bind();
    void unbind();
    
private:
    void _assert_target_bound();
    void _send_attribute(const ZBufferAttribute &attribute);
    
    friend ZGLVertexArray;
};

typedef std::shared_ptr<ZGLBuffer> ZGLBufferRef;

} // namespace zge
