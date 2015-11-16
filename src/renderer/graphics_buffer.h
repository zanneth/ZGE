/*
 * graphics_buffer.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/data.h>
#include <zge/noncopyable.h>
#include <zge/types.h>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <vector>

#define ZUNALLOCATED_BUFFER -1
#define ZUNBOUND_TARGET     -1

ZGE_BEGIN_NAMESPACE

struct ZBufferAttribute {
    unsigned       components_per_vertex;  // components per vertex attribute (1, 2, 3, or 4)
    ZComponentType component_type;         // data type of each component
    bool           normalized;             // whether fixed-point data values should be normalized
    size_t         stride;                 // byte offset between consecutive vertex attributes
    uintptr_t      offset;                 // offset of the first component of the first vertex attribute
};

struct ZPendingGraphicsBuffer {
    ZData        data;
    ZBufferUsage usage;
};

// -----------------------------------------------------------------------------

class ZGraphicsBuffer : ZNoncopyable {
public:
    virtual ~ZGraphicsBuffer();
    
    /// Returns the underlying name/identifier for this buffer.
    uint32_t get_name() const;
    
    /// Returns the rendering target initialized with this buffer.
    ZBufferTarget get_target() const;
    
    /// Adds an attributes that describes the format of this buffer.
    void add_attribute(ZBufferAttribute attribute);
    
    /// Returns all attributes associated with this buffer.
    std::vector<ZBufferAttribute> get_attributes() const;
    
    /// Clears all stored attributes with this buffer.
    void clear_attributes();
    
    /// Loads raw data into the buffer.
    void load_data(const ZData &data, ZBufferUsage usage);
    
    /// Loads raw data into the buffer.
    void load_data(const void *bytes, size_t length, ZBufferUsage usage);
    
    /// Returns data that is pending flush to the graphics processor.
    const ZPendingGraphicsBuffer& get_pending_buffer() const;
    
    /// Clears any data in the pending buffer.
    void clear_pending_buffer();
    
protected:
    // Only ZRenderContext can create buffers.
    ZGraphicsBuffer(uint32_t buffer_name, ZBufferTarget target, const std::function<void(uint32_t)> &deleter);
    friend class ZRenderContext;
    
private:
    uint32_t                        _buffer;
    ZBufferTarget                   _target;
    std::function<void(uint32_t)>   _deleter;
    std::vector<ZBufferAttribute>   _attributes;
    ZPendingGraphicsBuffer          _pending_buffer;
};

ZGE_DEFINE_SREF_TYPE(ZGraphicsBuffer);

// -----------------------------------------------------------------------------

class ZElementGraphicsBuffer : public ZGraphicsBuffer {
public:
    void set_elements_count(unsigned count);
    unsigned get_elements_count() const;
    
    void set_indices_type(ZComponentType type);
    ZComponentType get_indices_type() const;
    
protected:
    // Only ZRenderContext can create buffers.
    ZElementGraphicsBuffer(uint32_t buffer_name, const std::function<void(uint32_t)> &deleter);
    friend class ZRenderContext;
    
private:
    unsigned        _elements_count;
    ZComponentType  _indices_type;
};

ZGE_DEFINE_SREF_TYPE(ZElementGraphicsBuffer);

ZGE_END_NAMESPACE
