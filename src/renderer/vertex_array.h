/*
 * vertex_array.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#pragma once

#include <array>
#include <memory>
#include <zge/defines.h>
#include <zge/graphics_buffer.h>
#include <zge/noncopyable.h>
#include <zge/types.h>

BEGIN_ZGE_NAMESPACE

class ZRenderContext;

class ZVertexArray : ZNoncopyable, public std::enable_shared_from_this<ZVertexArray> {
    std::auto_ptr<struct ZVertexArrayImpl> _impl;
    
public:
    ZVertexArray();
    ~ZVertexArray();
    
    void add_buffer(ZGraphicsBufferRef buffer, ZVertexAttributeIndex index);
    void remove_buffer(ZVertexAttributeIndex index);
    void clear_buffers();
    
    ZGraphicsBufferRef get_buffer(ZVertexAttributeIndex index) const;
    std::array<ZGraphicsBufferRef, ZVERTEX_ATTRIB_COUNT> get_buffers() const;
    
    void set_element_buffer(ZElementGraphicsBufferRef element_buffer);
    ZElementGraphicsBufferRef get_element_buffer() const;
    
private:
    void _bind();
    friend ZRenderContext;
};

typedef std::shared_ptr<ZVertexArray> ZVertexArrayRef;

END_ZGE_NAMESPACE
