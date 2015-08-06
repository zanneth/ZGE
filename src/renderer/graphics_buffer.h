/*
 * graphics_buffer.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */
 
#pragma once

#include <zge/defines.h>
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

class ZGraphicsBuffer : ZNoncopyable {
public:
    ZGraphicsBuffer(ZBufferTarget target = ZBUFFER_TARGET_ARRAY);
    ZGraphicsBuffer(ZGraphicsBuffer&&);
    ~ZGraphicsBuffer();
    
    ZGraphicsBuffer& operator=(ZGraphicsBuffer&&);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZGraphicsBuffer);
    
    ZBufferTarget get_target() const;
    
    void             add_attribute(ZBufferAttribute attribute);
    std::vector<ZBufferAttribute> get_attributes() const;
    void             clear_attributes();
    
    void load_data(const void *data, size_t length, ZBufferUsage usage);
    
private:
    void _bind();
    void _unbind();
    void _move(ZGraphicsBuffer &&mv);
    
    friend class ZVertexArray;
    
private:
    uint32_t                        _buffer;
    ZBufferTarget                   _target;
    std::vector<ZBufferAttribute>   _attributes;
};

ZGE_DEFINE_SREF_TYPE(ZGraphicsBuffer);

class ZElementGraphicsBuffer : public ZGraphicsBuffer {
public:
    ZElementGraphicsBuffer();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZElementGraphicsBuffer);
    
    void set_elements_count(unsigned count);
    unsigned get_elements_count() const;
    
    void set_indices_type(ZComponentType type);
    ZComponentType get_indices_type() const;
    
private:
    unsigned        _elements_count;
    ZComponentType  _indices_type;
};

ZGE_DEFINE_SREF_TYPE(ZElementGraphicsBuffer);

ZGE_END_NAMESPACE
