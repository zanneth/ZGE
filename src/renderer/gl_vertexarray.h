/*
 * gl_vertexarray.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#pragma once

#include <initializer_list>
#include <memory>
#include <vector>
#include <zge/gl_buffer.h>
#include <zge/opengl.h>
#include <zge/noncopyable.h>

namespace zge {

class ZGLVertexArray : ZNoncopyable {
    GLuint _vertex_array_obj;
    std::vector<ZGLBufferRef> _buffers;
    
public:
    ZGLVertexArray(std::initializer_list<ZGLBufferRef> buffers = {});
    ZGLVertexArray(ZGLVertexArray &&);
    ~ZGLVertexArray();
    
    ZGLVertexArray& operator=(ZGLVertexArray &&);
    
    void add_buffer(ZGLBufferRef buffer);
    void remove_buffer(ZGLBufferRef buffer);
    void remove_all_buffers();
    std::vector<ZGLBufferRef> get_buffers();
    
    void bind();
    void unbind();
    bool is_bound();
    
private:
    void _enable_buffer_attribute(const ZBufferAttribute &attribute);
    void _disable_buffer_attribute(const ZBufferAttribute &attribute);
    friend ZGLBuffer;
};

typedef std::shared_ptr<ZGLVertexArray> ZGLVertexArrayRef;

} // namespace zge
