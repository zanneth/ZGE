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

BEGIN_ZGE_NAMESPACE

struct ZBufferAttribute {
    unsigned       components_per_vertex;  // components per vertex attribute (1, 2, 3, or 4)
    ZComponentType component_type;         // data type of each component
    bool           normalized;             // whether fixed-point data values should be normalized
    size_t         stride;                 // byte offset between consecutive vertex attributes
    uintptr_t      offset;                 // offset of the first component of the first vertex attribute
};

class ZGraphicsBuffer : ZNoncopyable {
    uint32_t _buffer;
    ZBufferTarget _target;
    std::vector<ZBufferAttribute> _attributes;

public:
    ZGraphicsBuffer(ZBufferTarget target = ZBUFFER_TARGET_ARRAY);
    ZGraphicsBuffer(ZGraphicsBuffer&&);
    ~ZGraphicsBuffer();
    
    ZGraphicsBuffer& operator=(ZGraphicsBuffer&&);
    
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
};

typedef std::shared_ptr<ZGraphicsBuffer> ZGraphicsBufferRef;

class ZElementGraphicsBuffer : public ZGraphicsBuffer {
    unsigned _elements_count;
    ZComponentType _indices_type;
    
public:
    ZElementGraphicsBuffer();
    
    void set_elements_count(unsigned count);
    unsigned get_elements_count() const;
    
    void set_indices_type(ZComponentType type);
    ZComponentType get_indices_type() const;
};

typedef std::shared_ptr<ZElementGraphicsBuffer> ZElementGraphicsBufferRef;

END_ZGE_NAMESPACE
