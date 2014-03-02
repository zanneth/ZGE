/*
 * graphics_buffer.h
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

#define ZUNALLOCATED_BUFFER -1
#define ZUNBOUND_TARGET     -1

BEGIN_ZGE_NAMESPACE

struct ZBufferAttribute {
    ZVertexAttributeIndex index;                  // generic vertex attribute index
    unsigned              components_per_vertex;  // components per vertex attribute (1, 2, 3, or 4)
    ZComponentType        component_type;         // data type of each component
    bool                  normalized;             // whether fixed-point data values should be normalized
    size_t                stride;                 // byte offset between consecutive vertex attributes
    uintptr_t             offset;                 // offset of the first component of the first vertex attribute
};

class ZVertexArray;

class ZGraphicsBuffer : ZNoncopyable {
    GLuint _buffer;
    ZBufferTarget _target;
    std::vector<ZBufferAttribute> _attributes;
    std::weak_ptr<ZVertexArray> _bound_vertex_array;

public:
    ZGraphicsBuffer();
    ZGraphicsBuffer(ZGraphicsBuffer&&);
    ~ZGraphicsBuffer();
    
    ZGraphicsBuffer& operator=(ZGraphicsBuffer&&);
    
    /* Accessors */
    ZBufferTarget get_target();
    void set_target(ZBufferTarget target);
    
    /* Attributes */
    void             add_attribute(ZBufferAttribute attribute);
    ZBufferAttribute get_attribute(ZVertexAttributeIndex index);
    std::vector<ZBufferAttribute> get_attributes() { return _attributes; }
    void             clear_attributes();
    
    /* Loading Data */
    void load_data(GLsizeiptr size, const GLvoid *data, GLenum usage);
    void load_subdata(GLsizeiptr offset, GLsizeiptr size, const GLvoid *data);
    
private:
    void _bind();
    void _unbind();
    
    void _assert_target_bound();
    void _move(ZGraphicsBuffer &&mv);
    void _send_attribute(const ZBufferAttribute &attribute);
    
    friend class ZVertexArray;
};

typedef std::shared_ptr<ZGraphicsBuffer> ZGraphicsBufferRef;

END_ZGE_NAMESPACE
