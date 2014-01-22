/*
 * vertexarray.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#pragma once

#include <initializer_list>
#include <memory>
#include <vector>
#include <zge/graphics_buffer.h>
#include <zge/opengl.h>
#include <zge/noncopyable.h>

namespace zge {

class ZVertexArray : ZNoncopyable {
    GLuint _vertex_array_obj;
    std::vector<ZGraphicsBufferRef> _buffers;
    
public:
    ZVertexArray(std::initializer_list<ZGraphicsBufferRef> buffers = {});
    ZVertexArray(ZVertexArray &&);
    ~ZVertexArray();
    
    ZVertexArray& operator=(ZVertexArray &&);
    
    void add_buffer(ZGraphicsBufferRef buffer);
    void remove_buffer(ZGraphicsBufferRef buffer);
    void remove_all_buffers();
    std::vector<ZGraphicsBufferRef> get_buffers();
    
    void bind();
    void unbind();
    bool is_bound();
    
private:
    void _enable_buffer_attribute(const ZBufferAttribute &attribute);
    void _disable_buffer_attribute(const ZBufferAttribute &attribute);
    friend ZGraphicsBuffer;
};

typedef std::shared_ptr<ZVertexArray> ZVertexArrayRef;

} // namespace zge
