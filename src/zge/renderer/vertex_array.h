/*
 * vertex_array.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#pragma once

#include <array>
#include <memory>
#include <set>
#include <zge/core/defines.h>
#include <zge/renderer/graphics_buffer.h>
#include <zge/core/noncopyable.h>
#include <zge/core/types.h>

ZGE_BEGIN_NAMESPACE

using ZVertexBuffersArray = std::array<ZGraphicsBufferRef, ZVERTEX_ATTRIB_COUNT>;

class ZVertexArray : ZNoncopyable {
public:
    virtual ~ZVertexArray();
    
    void add_buffer(ZGraphicsBufferRef buffer, ZVertexAttributeIndex index);
    void remove_buffer(ZVertexAttributeIndex index);
    void clear_buffers();
    
    uint32_t get_vao_name() const;
    
    const ZGraphicsBufferRef& get_buffer(ZVertexAttributeIndex index) const;
    const ZVertexBuffersArray& get_buffers() const;
    
    void set_element_buffer(ZElementGraphicsBufferRef element_buffer);
    const ZElementGraphicsBufferRef& get_element_buffer() const;
    
protected:
    /// Only ZRenderContext can create vertex arrays.
    ZVertexArray(uint32_t va_name, const std::function<void(uint32_t)> &deleter);
    friend class ZRenderContext;
    
private:
    uint32_t                        _vao;
    std::function<void(uint32_t)>   _deleter;
    ZElementGraphicsBufferRef       _element_buffer;
    ZVertexBuffersArray             _buffers;
    std::set<ZVertexAttributeIndex> _defined_attributes;
};

ZGE_DEFINE_SREF_TYPE(ZVertexArray);

ZGE_END_NAMESPACE
