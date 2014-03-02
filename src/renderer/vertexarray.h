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

BEGIN_ZGE_NAMESPACE

class ZVertexArray : ZNoncopyable {
    GLuint _vertex_array_obj;
    std::vector<ZGraphicsBufferRef> _buffers;
    std::vector<ZBufferAttribute> _enabled_attributes;
    
public:
    ZVertexArray(std::initializer_list<ZGraphicsBufferRef> buffers = {});
    ZVertexArray(ZVertexArray &&);
    ~ZVertexArray();
    
    ZVertexArray& operator=(ZVertexArray &&);
    
    void add_buffer(ZGraphicsBufferRef buffer);
    void remove_buffer(ZGraphicsBufferRef buffer);
    void remove_all_buffers();
    std::vector<ZGraphicsBufferRef> get_buffers();
    
private:
    void _bind();
    void _unbind();
    
    friend class ZRenderContext;
};

typedef std::shared_ptr<ZVertexArray> ZVertexArrayRef;

END_ZGE_NAMESPACE
